# magstripe-track-data

The magstripe-track-data reads track data from magstripe on your credit card.

# Note

Please note that I don't take any responsibility or liability for any damage or loss caused in case you use the software in illegally.
Use only for your technical interests.

# Usage

1. Connect a swipe magnetic card reader to your machine
2. Find device

```
cat /proc/bus/input/devices
```

You can see following output.

```
I: Bus=0003 Vendor=c216 Product=0101 Version=0111
N: Name="HID c216:0101"
P: Phys=usb-3f980000.usb-1.2/input0
S: Sysfs=/devices/platform/soc/3f980000.usb/usb1/1-1/1-1.2/1-1.2:1.0/0003:C216:0101.0001/input/input0
U: Uniq=
H: Handlers=sysrq kbd event0
B: PROP=0
B: EV=100013
B: KEY=e080ffdf 1cfffff ffffffff fffffffe
B: MSC=10
```

It means the device events can be read from `/dev/input/event0`.

3. Build on Linux

```
git clone git@github.com:hiroakis/magstripe-track-data.git
cd magstripe-track-data
gcc -Wall -o magstripe-reader main.c
```

4. Run

```
./magstripe-reader /dev/input/event0
```

5. Swipe your credit card

You can see Track1 and Track2 in the terminal that runs `magstripe-reader`. The card number, card holder name, Service Code (SVC), expiry date (YYMM) and Security Code (CVV) are printed.
On a side note, Securyty Code (CVV) is not equals to Security Code on the back of your card. 3-digits code on the back of card is another Security Code called CVV2 in Visa card. It's also called CVC in MasterCard.

```
%B4nnnnnnnnnnnnnn6^SANO/HIROAKI              ^YYMMSVC000000000000 00CVV000000?
;4nnnnnnnnnnnnnn6=YYMMSVC00000CVV00000?
```

# Platform

The operation has been confirmed with following devices.

- Machine: Raspberry Pi 3 Model B
- OS: 2018-11-13-raspbian-stretch-lite
- Magstripe reader: OSAYDE MSR90 USB (https://www.amazon.co.jp/dp/B014W1E7T2)

# License

MIT
