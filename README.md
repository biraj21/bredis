# Redis Clone in C

This project is inspired by the book [Build Your Own Redis with C/C++](https://build-your-own.org/redis/). I'm reading the book, understanding its concepts, and using this knowledge to improve the code as I work on building a basic Redis-like server from the ground up.

For details on the [resources](#resources) utilized in this project, please refer to the section provided below.

## Project Structure

The project is organized as follows:

```
src/
├── client/
│   ├── main.c
│   ├── <file.c>
│   ├── <file.h>
│   └── ...
├── server/
│   ├── main.c
│   ├── <file.c>
│   ├── <file.h>
│   └── ...
└── shared/
    ├── <file.c>
    └── <file.h>
Makefile
```

- **src/client:** This directory contains the code and resources for the client-side of our Redis clone. The client is responsible for interacting with the server, sending commands, and receiving responses.

- **src/server:** The server-side of our Redis clone resides here. This is where we implement the core functionality of the Redis-like database, handling data storage and retrieval, and managing client connections.

- **src/shared:** Common code and resources shared between the client and server are stored in this directory. It includes code that both components depend on, ensuring consistency and efficiency in the project.

## Resources

- [Build Your Own Redis with C/C++](https://build-your-own.org/redis/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/multi/index.html)
- [Johannes 4GNU_Linux's YouTube video](https://www.youtube.com/watch?v=O-yMs3T0APU)
