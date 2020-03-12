using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using MQTTnet;
using MQTTnet.Client;
using MQTTnet.Client.Options;
using Newtonsoft.Json;

namespace RT.IOTWorkshop.Infrastructure.MQTT
{
    public class MQTTProvider
    {
        private readonly IMqttClientOptions options;
        public IMqttClient Client { get; private set; }
        private Dictionary<string, Action<string>> actions = new Dictionary<string, Action<string>>();

        public bool Connected => Client.IsConnected;

        public MQTTProvider(string broker)
        {
            var factory = new MqttFactory();
            var client = factory.CreateMqttClient();

            options = new MqttClientOptionsBuilder()
                .WithClientId(".NetClient_IOWorkshop")
                .WithTcpServer(broker)
                .Build();


            client.UseApplicationMessageReceivedHandler((e) =>
            {
                actions[e.ApplicationMessage.Topic](Encoding.UTF8.GetString(e.ApplicationMessage.Payload));
            });

            Client = client;
        }

        ~MQTTProvider()
        {
            Client.DisconnectAsync().Wait();
            Client.Dispose();
        }

        public async Task Publish(string topic, string msg)
        {
            var message = new MqttApplicationMessageBuilder()
              .WithTopic(topic)
              .WithPayload(msg)
              .WithExactlyOnceQoS()
              .WithRetainFlag()
              .Build();

            if (!Client.IsConnected)
                await Client.ConnectAsync(options);

            await Client.PublishAsync(message);
        }

        public async Task Publish(string topic, object msg)
        {
            var message = new MqttApplicationMessageBuilder()
              .WithTopic(topic)
              .WithPayload(JsonConvert.SerializeObject(msg))
              .WithExactlyOnceQoS()
              .WithRetainFlag()
              .Build();

            if (!Client.IsConnected)
                await Client.ConnectAsync(options);

            await Client.PublishAsync(message);
        }

        public async Task Subscribe(string topic, Action<string> callback)
        {

            if (!Client.IsConnected)
                await Client.ConnectAsync(options);

            await Client.SubscribeAsync(new TopicFilterBuilder().WithTopic(topic).Build());
            actions.Add(topic, callback);
        }


    }
}
