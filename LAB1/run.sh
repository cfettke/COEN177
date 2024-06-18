#!/bin/sh

# Function to calculate the area and perimeter of a circle
circle() {
    echo "Enter radius of circle: ";
    read radius

    if [ "$radius" -gt 0 ] 
    then
        perimeter=$(echo "scale=2; 2 * 3.14 * $radius" | bc)
        area=$(echo "scale=2; 3.14 * $radius * $radius" | bc)
        echo "The perimeter of the circle is $perimeter units."
        echo "The area of the circle is $area square units."
    else
        echo "Invalid radius. Please enter a positive numeric value."
        return 1
    fi
}
rectangle() {
    rectangle area calc
    echo "Enter height of rectangle: ";
    read height
    echo "Enter width of rectangle: ";
    read width
    area=`expr $height \* $width`
    echo "The area of the rectangle is $area";
    echo "Would you like to repeat for another rectangle [Yes/No]?";
    read response
}

# Start of the main script
echo "Executing $0"
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME=$HOME"
echo "USER=$USER"
echo "PATH=$PATH"
echo "PWD=$PWD"
echo "\$\$=$$"
user=$(whoami)
numusers=$(who | wc -l)
echo "Hi $user! There are $numusers users logged on."
if [ "$user" = "cfettkether" ] 
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi

response="Yes"
while [ "$response" != "No" ]
do
    # Call the circle function to perform its logic
    circle

    echo "Would you like to repeat for another circle [Yes/No]?"
    read response
done
