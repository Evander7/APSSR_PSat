import socketserver

class MyTCPHandler(socketserver.BaseRequestHandler):
    """
    The request handler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """

    def handle(self):
        # self.request is the TCP socket connected to the client
        self.data = True;
        while self.data:
            self.data = self.request.recv(1024).strip()
            print("{} wrote: {}".format(self.client_address[0], self.data))
            # just send back the same data, but upper-cased
            self.request.sendall(b"\n")
            with open("test.txt", "a") as myfile:
                myfile.write("{} \n".format(self.data.decode("utf-8")))

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

if __name__ == "__main__":
    HOST, PORT = "0.0.0.0", 1619

    server = ThreadedTCPServer((HOST, PORT), MyTCPHandler)
    # Activate the server; this will keep running until you  
    # interrupt the program with Ctrl-C
    server.serve_forever()
