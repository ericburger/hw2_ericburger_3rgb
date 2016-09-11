###############################################################################
#
# The MIT License (MIT)
#
# Copyright (c) Tavendo GmbH
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
###############################################################################

import sys
from twisted.internet import reactor
from autobahn.twisted.websocket import WebSocketClientFactory, \
    WebSocketClientProtocol, \
    connectWS
    
import serial

class BroadcastClientProtocol(WebSocketClientProtocol):

    """
    Simple client that connects to a WebSocket server, send a HELLO
    message every 2 seconds and print everything it receives.
    """


    def onOpen(self):
        print("WebSocket connection open.")

        def checkSerial():
            if ser.inWaiting() > 0:
                # Wait until byte is read
                try:
                    # Read entire line
                    # (until '\n')
                    x = ser.readline()
                    self.sendMessage( x.encode('utf8') )
                except:
                    pass
            
            self.factory.reactor.callLater(0.1, checkSerial)

        # start sending messages every second ..
        checkSerial()

    def onMessage(self, payload, isBinary):
        if not isBinary:
            print("Text message received: {}".format(payload.decode('utf8')))


if __name__ == '__main__':

    # Change the port name to match the port
    # to which your Arduino is connected.
    serial_port_name = 'COM4' # for Windows
    ser = serial.Serial(serial_port_name, 9600, timeout=1)

    factory = WebSocketClientFactory(u"ws://127.0.0.1:9000")
    factory.protocol = BroadcastClientProtocol
    connectWS(factory)

    reactor.run()

