# Netlink notes

## iproute2 dumps

### Add rmnet_data0 link

```text
oneplus-enchilada:~/iproute2$ sudo ip link add link rmnet_ipa0 name rmnet_data0 type rmnet mux_id 1 egress-chksumv4 ingress-chksumv4 ingress-deaggregation

// First check if the iface already exists
Resizing from 32 to 40
Adding attr type 29
ATTR:
09:00:00:00

Resizing from 40 to 56
Adding attr type 3
ATTR:
72:6d:6e:65:74:5f:69:70:61:30:00

Sending...:
38:00:00:00:12:00:01:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:08:00:1d:00:09:00:00:00:0f:00:03:00:72:6d:6e:65:74:5f:69:70:61:30:00:00

// Now add the link
Resizing from 32 to 40
Adding attr type 5          // IFLA_LINK
ATTR:
03:00:00:00                 // index of rmnet_ipa0

Resizing from 40 to 56
Adding attr type 3          // name of new link
ATTR:
72:6d:6e:65:74:5f:64:61:74:61:30:00  // "rmnet_data0"

NEST START: Resizing from 56 to 60
Adding attr type 18         // IFLA_LINKINFO (nested attribute)
ATTR:
Resizing from 60 to 72
Adding attr type 1          // IFLA_INFO_KIND
ATTR:
72:6d:6e:65:74              // "rmnet"

NEST START: Resizing from 72 to 76
Adding attr type 2          // IFLA_INFO_DATA (rmnet data)
ATTR:
Resizing from 76 to 84
Adding attr type 1          // mux id
ATTR:
01:00

Resizing from 84 to 96
Adding attr type 2         // rmnet flags
ATTR:
0d:00:00:00:ff:ff:ff:ff

NEST END
NEST END
Sending...:
60:00:00:00:10:00:01:06:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:08:00:05:00:03:00:00:00:10:00:03:00:72:6d:6e:65:74:5f:64:61:74:61:30:00:28:00:12:00:09:00:01:00:72:6d:6e:65:74:00:00:00:18:00:02:00:06:00:01:00:01:00:00:00:0c:00:02:00:0d:00:00:00:ff:ff:ff:ff
```

### Setting the IP address

The packet generation has been re-ordered for readability. iproute2
checks to see if the link is valid before trying to give it an IP
address.

```text
oneplus-enchilada:~$ sudo ip address add 10.37.74.124/30 dev rmnet_data0

// This checks to see if the link is valid
Resizing from 32 to 40
Adding attr type 29          // IFLA_EXT_MASK ?
ATTR:
09:00:00:00                  // RTEXT_FILTER_VF | RTEXT_FILTER_SKIP_STATS

Resizing from 40 to 56
Adding attr type 3
ATTR:
72:6d:6e:65:74:5f:64:61:74:61:30:00

Sending...:
38:00:00:00:12:00:01:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:
00:00:00:00:00:08:00:1d:00:09:00:00:00:10:00:03:00:72:6d:6e:65:74:5f:64:61:74:61:
30:00

// Now assign the IP, which link to assign it to is in the header
Resizing from 24 to 32
Adding attr type 2           // IFA_LOCAL
ATTR:
0a:25:4a:7c

Resizing from 32 to 40
Adding attr type 1           // IFA_ADDRESS
ATTR:
0a:25:4a:7c                  // 10.37.74.124

Sending...:
28:00:00:00:14:00:01:06:00:00:00:00:00:00:00:00:
ifa_family  ifa_prefixlen
02:         1e:            00:00:05:00:00:00:08:00:02:
00:0a:25:4a:7c:08:00:01:00:0a:25:4a:7c
```

### Adding the default route

```text
oneplus-enchilada:~$ sudo ip route add default via 10.37.74.125 dev rmnet_data0
Resizing from 28 to 36

// This checks to see if the link is valid
Resizing from 32 to 40
Adding attr type 29
ATTR:
09:00:00:00

Resizing from 40 to 56
Adding attr type 3
ATTR:
72:6d:6e:65:74:5f:64:61:74:61:30:00 

Sending...:
38:00:00:00:12:00:01:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:
00:00:00:00:00:08:00:1d:00:09:00:00:00:10:00:03:00:72:6d:6e:65:74:5f:64:61:74:61:
30:00 

// Now set the route

Adding attr type 5
ATTR:
0a:25:4a:7d               // 10.37.74.125

Resizing from 36 to 44
Adding attr type 4
ATTR:
05:00:00:00 

Sending...:
2c:00:00:00:18:00:01:06:00:00:00:00:00:00:00:00:
family dst_len src_len tos   table proto scope type  flags
02     :00     :00     :00   :fe   :03   :00   :01   :00:00:00:00

:08:00:05:00:0a:25:4a:7d:08:00:04:00:05:00:00:00 
```

2c:00:00:00:18:00:01:06:00:00:00:00:00:00:00:00
family dst_len src_len tos   table proto scope type  flags
02     :00     :00     :00   :fe   :03   :00   :01   :00:00:00:00
:08:00:05:00:0a:25:4a:7d:08:00:04:00:06:00:00:00


### link set address

nlmsghdr
28:00:00:00:14:00:01:06:00:00:00:00:00:00:00:00  :02:1e:00:00:05:00:00:00:08:00:02:00:0a:25:4a:7c:08:00:01:00:0a:25:4a:7c
28:00:00:00:14:00:01:06:00:00:00:00:00:00:00:00  :02:21:00:00:06:00:00:00:08:00:02:00:0a:25:4a:7c:08:00:01:00:0a:25:4a:7c
