# Server

```sh
openssl genrsa -out key.pem
openssl req -new -key key.pem -out csr.pem
openssl x509 -req -days 9999 -in csr.pem -signkey key.pem -out cert.pem
rm csr.pem
```

Enable https on localhost with invalid cert
`chrome://flags/#allow-insecure-localhost`

## Required Headers

[Headers required for SharedArray Buffer](https://web.dev/coop-coep/)
