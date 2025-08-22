# Code Citations

## License: unknown
https://github.com/KoleckOLP/masq_server/tree/d438c5a4549037c7b31235c77f8edfdb4b9fff1d/old/main-cgi-post.py

```
socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)
    print(f"Listening on port {PORT}...")
    while True:
        conn, addr = s.accept()
        with conn:
            print(
```

