It is very easy to create a `client` for our server.

Follow these instructions:

<br />
<br />


### In order to create a client, you need:


1. To create your client, like that:
```c++
client client;
```

2. Then to initalize the host and the port, by calling the init method:
```c++
client.init("your_host", "your_port");
```

3. Then start your client thread by calling this method:
```c++
client.startClientThread();
```

### Your client is now ready to receive messages from the server.
### To send a message to the server, simply use this method by giving a string as only parameter:

```c++
client.sender("your_message");
```

### When you receive a message from the server, it will be added to this vector:
```c++
SafeQueue<std::string> _msg_queue;
```

### That's it, you're now all setup to create your own client dirrecly connected to the server ! 
