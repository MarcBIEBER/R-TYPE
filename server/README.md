## Server Protocol

### The server protocol is a simple text-based protocol. It is designed to be easy to implement. The protocol is line-based, with each line terminated by a newline character. The first word of each line is a command, and the rest of the line is the command's arguments. The server protocol is case sensitive.


### The server is the `Brain` of the game, it handles the game logic and the communication with the clients, the spawn rate of the enemies and the game stages. The server is the only one that can modify the game state and the only one that can send messages to the clients.



You can connect to the server using our game client. The server listens on port passed as the first argument to the server executable. The server will not start if the port is already in use.

We can easily create multiple instances of the server by passing the number of instances we want to create as a second argument to the server executable. The server will not start if the port is already in use.


The server uses a safeQueue to handle correctly the messages sent by the clients. and vis-versa.
Eatch action is handled by a thread, so the server can handle multiple clients at the same time and the server can handle multiple actions at the same time.

1. The server will send a `WELCOME` message to the client when the client connects. The `WELCOME` message contains the player's id, which is a number between 1 and 4.

2. The server will send a `GAME_START` message to the client when the game starts. The `GAME_START` message contains the number of players in the game.

3. The server handle the current stage of the game.

    Every 2 sec the server will send a 'STATUS' message to the client. The 'STATUS' message contains the player's id, which is a number between 1 and 4, the player's position the current stage and the progress of the current stage.

    When a Client shoot a bullet, the server will send a `SHOOT` message to the client. The `SHOOT` message contains the player's id, which is a number between 1 and 4, and the player's position.

    It's up to the client to decide when to send the `MOVE` command. The server will send a `MOVE` message to the client when the client's player moves. The `MOVE` message contains the player's id, which is a number between 1 and 4, and the player's position.

4. The server will choose when and where the enemies will spawn. The server will send a `SPAWN_ENEMY` message to the client when an enemy spawns. The `SPAWN_ENEMY` message contains the enemy's id, which is a number between 1 and 4, and the enemy's position.
 
5. The server will send a `PLAYER_ELIMINATED` message to the client when that client is eliminated from the game.

    The server will send a `PLAYER_DISCONNECTED` message to the client when that client disconnects from the game.


6. The server will send a `GAME_END` message to the client when the game ends.

## Let's see the server protocol in action!

The commands are composed in the following way:

PREFIX ARGUMENTS

Let's check all the prefixes and their arguments:

* "E EnnemyType PosX PosY" - Spawn an ennemy of type EnnemyType at position (PosX, PosY)

* "p StateOfTheProgressBar" - Update the state of the progress bar

* "S Stage" - Update the current stage

* "b angle" - Shoot a boss bullet with the given angle

* "m Angle1 Angle2" - Shoot a bullet with the given angle

* "bossS AcctualStage" - Create a boss

* "b2" - Spawn a mini boss

* "+ bonusId PosX PosY" - Spawn a bonus at position (PosX, PosY)

### Now the client commands:

* "PlayerId Direction" - Move the player in the given direction

* "B PlayerId posX posY" - Shoot a bullet at position (PosX, PosY)

* "start" - Start the game

In game console commande:

* "quit" - Quit the game and disconnect from the server

* "clear" - Clear the console

* "max" - Activate the cheat mode (infinity shoot)

* "boss" - Spawn a boss

* "miniboss" - Spawn a mini boss

* "M playerId message" - Send a message to all the players connected to the server (chat Box)

* "k playerId" - Use to handle ping

* "P playerId posX poY" - Send the position of the player to the server (handle rollback, etc...)