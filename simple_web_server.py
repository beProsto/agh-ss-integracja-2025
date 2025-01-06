from http.server import SimpleHTTPRequestHandler, HTTPServer

# Define the handler to serve files and directories from the current directory


class MyHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        return super().do_GET()

# Set up the web server


def run(server_class=HTTPServer, handler_class=MyHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting server on port {port}...")
    httpd.serve_forever()


if __name__ == '__main__':
    run()
