@ECHO OFF
echo "IPv4 Adresses"
ipconfig | findstr /R /C:"IPv4 Address" /C:"Subnet Mask"
echo.
echo "Date is "
date /t
echo.
echo "Time is"
time /t
echo.
echo "ARP table is"
arp -a
echo.
echo "Network Connection information"
ipconfig
PAUSE