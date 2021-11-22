# Serial connections
Raspberry pi4 to Arduino Pro mini i2c protocol and Arduino Pro mini to Arduino Leonardo UART connection example.

1. Compile i2c Master
```bash
  gcc i2c_master.cpp -o i2c_master -lstdc++ -lwiringPi
```

2. Upload code to Arduino boards.

3. Run Master
```bash
  ./master/i2c_master
```

