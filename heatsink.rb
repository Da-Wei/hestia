require 'thread'
require 'RRD'
require 'rmodbus'
include ModBus


class HeatSink

  def initialize(name, address, serial, speed)
    @name = name
    client = RTUClient.new(serial, speed)
    @device = client.with_slave(address)
    @semaphore = Mutex.new
    @mode = { :summer => 1, :winter => 0 }
  end

  def on
    @semaphore.synchronize do
      @device.write_single_coil 54, 1
    end
  end

  def off
    @semaphore.synchronize do
      @device.write_single_coil 54, 0
    end
  end

  def get_status
    @semaphore.synchronize do
      @device.read_coils 54, 1
    end
  end

  def set_mode(mode)
    if @mode.has_key?(mode)
      @semaphore.synchronize do
        @device.write_single_coil 55, mode
      end
    end
  end

  def get_mode
    @semaphore.synchronize do
      @device.read_coils 55, 1
    end
  end

  def sensor
    @semaphore.synchronize do
      result = @device.read_holding_registers 70, 4
      result.map { |x| x.fdiv(10) }
    end
  end

  def monitor(store=false, data_path)
    if not File.exists?("#{data_path}/#{@name}_temp.rrd")
      RRD.create(    
                 "#{data_path}/#{@name}_sensors.rrd",
                 "--start", "#{Time.now.to_i - 1}",
                 "--step", "60",
                 "DS:B1:GAUGE:120:-50:100",
                 "DS:B2:GAUGE:120:-50:100",
                 "DS:B3:GAUGE:120:-50:100",
                 "DS:B4:GAUGE:120:-50:100",
                 "RRA:LAST:0.5:1:1440",
                 "RRA:AVERAGE:0.5:30:336",
                 "RRA:AVERAGE:0.5:60:8760",
                 "RRA:MIN:0.5:60:8760",
                 "RRA:MAX:0.5:60:8760"
                 )
    end
    Thread.new do
      loop do
        start_time = Time.now
        @values = sensor
        if store
          RRD.update(
                     "#{data_path}/#{@name}_sensors.rrd",
                     "#{Time.now.to_i}:#{@values.join(':')}"
                     )
        end

        elapsed = Time.now - start_time
        sleep([60 - elapsed, 0].max)
      end
    end
  end
end
