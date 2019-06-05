# -*- coding: utf-8 -*-

import hashlib


class URLShortener():

    def __init__(self):
        self.short_to_url_map = dict()
        self.m = hashlib.sha256
        self.prefix = 'http://urlso.rt/'

    def shorten(self, url):
        sha_signature = self.m(url.encode()).hexdigest()
        short_hash = sha_signature[:6]
        self.short_to_url_map[short_hash] = url
        return self.prefix + short_hash

    def restore(self, short):
        short_hash = short.replace(self.prefix, '')
        return self.short_to_url_map[short_hash]


if __name__ == '__main__':
    url = 'https://www.google.com/demo'
    s = URLShortener()
    short = s.shorten(url)
    print('\n original: {}'.format(url))
    print(' short: {}'.format(short))
    print(' restored: {}'.format(s.restore(short)))
