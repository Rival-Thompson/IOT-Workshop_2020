using System;
using System.Threading.Tasks;
using RT.IOTWorkshop.Infrastructure.MQTT;

namespace RT.IOTWorkshop.ConsoleApp
{
  class Program
  {
    private static MQTTProvider provider;

    static async Task Main(string[] args)
    {
      Console.WriteLine("Hello World!");
      provider = new MQTTProvider("mqtt.fluux.io");

      await Subscribe();

      await PublishAsync();
      Console.ReadLine();
    }

    private static async Task PublishAsync()
    {
      await provider.Publish("iotworkshop/tst", "hello world");
    }

    private static void MessageRecieved(string msg)
    {
      Console.WriteLine(msg);
    }

    private static async Task Subscribe()
    {
      await provider.Subscribe("iotworkshop/tst", MessageRecieved);
    }
  }
}
