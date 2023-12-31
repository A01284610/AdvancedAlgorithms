# TC2008B. Sistemas Multiagentes y Gráficas Computacionales
# Python server to interact with Unity
# Sergio. Julio 2021

from http.server import BaseHTTPRequestHandler, HTTPServer
import logging
import json

import numpy as np
from boid import Boid

# Size of the board:
width = 30
height = 30
num_boids = 20

# Set the number of agents here:
flock = [Boid(*np.random.rand(2) * 30, width, height) for _ in range(num_boids)]


def update_positions():
    global flock
    data = {
        'colour': "",
        'kind': "",
        'pos': ""
    }
    for boid in flock:
        boid.apply_behaviour(flock)
        boid.update()
        pos = boid.edges()    
        data['colour'] = boid.colour
        data['kind'] = boid.kind
        data['pos'] = pos
    return list(data)


def features_to_json(ps):
    posDICT = []

    for p in ps:

        data = {
            'colour': p[0],
            'kind': p[1],
            'pos': {
                'x': p[2][0],
                'z': p[2][1],
                'y': p[2][2]
            }
        }
        print("asdasdasd")
        print(data)
        posDICT.append(data)


    # for p in ps:
    #     pos = {
    #         "x": p[0],
    #         "z": p[1],
    #         "y": p[2]
    #     }
        # posDICT.append(pos)
    return json.dumps(posDICT)


class Server(BaseHTTPRequestHandler):

    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        logging.info("GET request,\nPath: %s\nHeaders:\n%s\n", str(self.path), str(self.headers))
        self._set_response()
        self.wfile.write("GET request for {}".format(self.path).encode('utf-8'))

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        # post_data = self.rfile.read(content_length)
        post_data = json.loads(self.rfile.read(content_length))
        # logging.info("POST request,\nPath: %s\nHeaders:\n%s\n\nBody:\n%s\n",
        # str(self.path), str(self.headers), post_data.decode('utf-8'))
        logging.info("POST request,\nPath: %s\nHeaders:\n%s\n\nBody:\n%s\n",
                     str(self.path), str(self.headers), json.dumps(post_data))

        '''
        x = post_data['x'] * 2
        y = post_data['y'] * 2
        z = post_data['z'] * 2
        
        position = {
            "x" : x,
            "y" : y,
            "z" : z
        }

        self._set_response()
        #self.wfile.write("POST request for {}".format(self.path).encode('utf-8'))
        self.wfile.write(str(position).encode('utf-8'))
        '''

        positions = update_positions()
        # print(positions)
        self._set_response()
        resp = "{\"data\":" + features_to_json(positions) + "}"
        # print(resp)
        # print("asdasdasdasd")
        self.wfile.write(resp.encode('utf-8'))


def run(server_class=HTTPServer, handler_class=Server, port=9090):
    logging.basicConfig(level=logging.INFO)
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    logging.info("Starting httpd...\n")  # HTTPD is HTTP Daemon!
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:  # CTRL+C stops the server
        pass
    httpd.server_close()
    logging.info("Stopping httpd...\n")


if __name__ == '__main__':
    from sys import argv

    if len(argv) == 2:
        run(port=int(argv[1]))
    else:
        run()
