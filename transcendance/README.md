# Transcendance

<p align="center">
  <img width="256" height="256" src="https://github.com/senolem/PaddleBattle/blob/74b4eb69757c8f5e3705d27b23f3512cc9286668/assets/Textures/logo.png">
  <table align="center">
    <tr>
        <td align="center"><strong><em>Paddle Battle, an overcomplicated name for a simple Pong game.</em></strong></td>
    </tr>
</table>
</p>

Game repo: https://github.com/senolem/PaddleBattle

## Usage/Examples

To start the project using Docker compose
```console
make
```

To start only one part of the project using Docker
```console
make db | front-container | back-container
```

To start only one part of the project using npm (backend cannot be started without the database)
```console
make front | back
```
## Features
- Entirely hand-made NestJS API and Vue 3 frontend with in-game integrations
- Profiles with customization, match history
- Friends system
- Socket.IO realtime chat system, rooms and private messages, Colyseus integrations
- Client-side prediction (I tried), client-side physics engine using cannon-es

## Team
albaur, averon and faventur
