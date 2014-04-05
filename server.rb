require 'sinatra/base'
require 'data_mapper'
require 'json'
require './models'

DataMapper::Logger.new($stdout, :debug)

DataMapper.setup(:default, ENV['DATABASE_URL'] || "sqlite3://#{Dir.pwd}/development.db")

DataMapper.auto_migrate!

class HestiaServer < Sinatra::Base
  set :sessions, true

  get '/' do
    'Hestia Server - v0.1'
  end

  post '/device' do
    params = JSON.parse(request.env["rack.input"].read)
    if params["type"]=="ModbusDevice"
      obj=ModbusDevice.create params
    else
      obj=Device.create params
    end
    obj.to_json
  end

  get '/device' do
    case params[:type]
    when 'ModbusDevice'
      devices = ModbusDevice.all
      devices.to_json
    else
      devices = Device.all
      devices.to_json(:only => [:id, :name, :type, :enabled])
    end
  end

  get '/device/:id' do
    device = Device.get(params[:id])
    case device[:type]
    when 'ModbusDevice'
      ModbusDevice.get(params[:id]).to_json
    else
      device.to_json
    end
  end

  get '/modbus/get/:id' do
    var = ModbusVar.get(params[:id])
    var.get
  end

  run! if app_file == $0
end

