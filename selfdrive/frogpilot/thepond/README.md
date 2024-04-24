# Thepond

This is a new way to manage your frogpilot device. It allows you to change most settings that you can edit in on the device, as well as view the video stream and download the logs.

### To run using docker:

```bash
docker build -t thepond .
docker run -v $(pwd):/app --rm -ti -p 8084:8084 thepond
```

### Run and debug on comma device (or computer with python)

```bash
./start.sh
```
