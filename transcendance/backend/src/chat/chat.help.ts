export const helpPage =
`Available commands:

/help
Print this help page

/join roomName [password]
Join a room

/leave
Leave the current room to go back to main

/createroom roomName [public|private]
Create a room and join it, privacy is set to public by default

/password
Show the current room password (only if private)

/rooms
Display currently available public rooms

/users
Display current room connected users

/here
Display current room joined users

/clear
Clear all chat messages
`

export const helpPageOperator =
`
(Operator only)

/op username
Adds the operator status to a user for a room

/deop username
Remove the operator status from a user for a room

/kick username
Kick a user from a room

/ban username
Ban a user from a room (until they are unbanned)

/unban username
Unban a user

/mute username timeout
Ban a user from a room for a certain amount of time (defined in seconds);
the minimum time required is 1 second, the maximum limit is 5 days (432000 seconds)

/privacy [public|private]
Change the current room privacy

/newpassword
Generate a new password for the room
`

export const helpPageAdmin =
`
(Administrator only)

/broadcast
Broadcast a message to all active users
`
