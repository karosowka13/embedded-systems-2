//creating Web socet
const WebSocket = require('ws')

const wss = new WebSocket.Server({ port: 'SERIAL PORT' })

wss.on('connection', ws => {
  ws.on('message', message => {
    console.log(`Received message => ${message}`)
  });

  ws.on('error',error => {
    console.log(`WebSocket error: ${error}`)
  });
})