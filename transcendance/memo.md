# Transcendance

Welcome to Transcendance, a project of website with a multiplayer version of the game of Pong, an online chat and a profile page for each registered user with graphs displaying the statistics of the games they have played. For the database we use PostrgreSQL while the server backend is run by Node.js and uses NestJS and Sequelize. NestJs is an MVC framework for building efficient, scalable Node.js server-side applications, providing tight integrations with Sequelize out of the box with the @nestjs/sequelize packages. Sequelize is an Object Relational Mapper (ORM) for Node.js used to interact with Postgres databases.

Tutorials that may be useful for understanding how a backend is made and how it works are __How to Build Web APIs with NestJS, Postgres, and Sequelize - A Beginner's Guide__ by Victor Onwuzor for [FreeCodeCamp](https://www.freecodecamp.org/news/build-web-apis-with-nestjs-beginners-guide),

__Nestjs Pipes__ by [NextJSVietnam](https://nextjsvietnam.com/post/nestjs-pipes),

___Build a Real-Time Chat API Using WebSockets in NestJS__ by Timilehin Omolana on [www.makeuseof.com](https://www.makeuseof.com/build-real-time-chat-api-using-websockets-nestjs),

and __Build a real-time chat application with Nestjs and PostgreSQL__ by  Ekekenta Odionyenfe for [Arctype](https://arctype.com/blog/postgres-nestjs).

For further information on Node.js and NestJS, see also __Node JS Tutorial Français pour Débutant - Cours complet 8h [2022]__ by Simon Dieny on his [Youtube channel](https://www.youtube.com/watch?v=NRxzvpdduvQ),

and __NestJs Course for Beginners - Create a REST API__ by Vladimir Agaev on [FreeCodeCamp Youtube channel](https://www.youtube.com/watch?v=GHTA143_b-s&t=4393s).

The Wikipedia page of the original project of Pong (1972) is very interesting:
<https://en.wikipedia.org/wiki/Pong>.

Here is some useful material we used for the project:

### General Framework Documentation:

This project has been made using [Typescript](https://www.typescriptlang.org/docs), a script language offering all of [JavaScript](https://developer.mozilla.org/en-US/docs/Web/JavaScript)’s features, plus an additional layer on top of these, TypeScript’s type system.

For the front-end we used [VueJS](https://vuejs.org/guide/introduction.html) and [Vuetify](https://vuetifyjs.com/en), and for the back-end we used [NestJS](https://docs.nestjs.com).

The databse we use is [PostgreSQL](https://www.postgresql.org) and the ORM used to interface with it is [Sequelize](https://sequelize.org/docs/v6/getting-started).

In addition to the above mentioned official documentation, we took inspiration from other references, that follow.

### Tooltips and Buttons:

We wanted to implement the hover functionality on certain buttons, and to trigger a menu with the right button of the mouse. To achieve the first goal in VueJS we had to use a boolean variable and the @mouseenter and @mouseleave properties of Vue <btn> tags, as follows:
```
@mouseenter="hover = true"
@mouseleave="hover = false"
```
as explained [here](https://codingbeauty.medium.com/vue-hover-c8b8eb786814).

For achieving the second goal, that we eventually abandoned, we had to properly understand how to fire an event with the mouse in Javascript, described [here](https://nikitahl.com/detect-mouse-right-click-with-javascript) and [here](https://stackoverflow.com/questions/2405771/is-right-click-a-javascript-event).

Javascript also offered us other interesting properties, such as the ability to spot the [browser in use](https://stackoverflow.com/questions/9847580/how-to-detect-safari-chrome-ie-firefox-and-opera-browsers) or to obtain the [dimensions](https://gist.github.com/zmts/3388e16fe6b2983a541e91c40fcc2eb3) of an image from a file.

### Forms and Uploads:

To add a layer of safety to forms in the front-end, we can ask for a [form of validation](https://stackoverflow.com/questions/59172455/how-validate-two-file-input-with-vue-js) on our form and we need to be sure that [the formdata be not empty](https://stackoverflow.com/questions/40364692/check-if-formdata-is-empty) before sending it.

For receiving the files in the back-end, through axios requests, we used [multer files](https://gabrieltanner.org/blog/nestjs-file-uploading-using-multer).

### chartJs:

- <https://www.w3schools.com/ai/ai_chartjs.asp>
- <https://github.com/chartjs/chartjs-adapter-luxon>
- <https://www.chartjs.org/docs/latest/samples/scales/time-line.html>
- <https://www.youtube.com/watch?v=y9wcQnIRc_Y>