# Connected Canvas

This project is a simple scribble application.
Users can create rooms that will synchronize their canvas with the users present in the same room.

A NodeJS API stores accounts information in a 'Lowdb' database, manages online users and opened rooms.
Lowdb is a very light database that stores data in a JSON file.

## How does it work ?
- After creating an account, you will be able to open your own room, and if you want, set a password to it.
- At this point, other users will see your room in the roomlist.
- By joining it, their current canvas will be added to the layers list of your room, you will also have their name appearing in your displayed layers list.
- Every .5 seconds, every user will send a request to the API that will update the canvas at their name if it changed, and return a list of refreshed canvasses.
- At this point, each canvas will be added to your displayed painter, if you indicated it to be shown, with the order of your choice.

## To do
- [ ] Manage friends list
- [ ] Save canvasses
- [ ] Chat
- [ ] Make online paint faster 

<img width="1000" alt="Failure to load image, open there" src="https://drive.google.com/uc?export=view&id=1sEV66mAAM43anr6VuTNWC3rmCPsQa9rO">
