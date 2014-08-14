#!/usr/bin/env python
#coding:utf-8

import httplib2
import sys
import time

def upddns():
    h = httplib2.Http(".cache")
    h.add_credentials(username, password)
    try:
        resp, content = h.request(url+hostname,"GET")
    except httplib2.HttpLib2Error,e:
        print "Error retrieving data:",e
        sys.exit(1)
    return (resp,content)

if __name__=="__main__":
    username="mawag"
    password="wbdx3300"
    hostname="mawag.oicp.net"
    url="http://ddns.oray.com/ph/update?hostname="

    if "good" or "nochg" in upddns()[1]:
        print "update ip ok!"
        sys.exit(0)
    else:
        print "update ip faild,retry..."
        time.sleep(11)
        upddns()

