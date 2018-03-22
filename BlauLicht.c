#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "gattlib.h"



int set_color(gatt_connection_t *connection, short r, short g, short b, short w)
{
	uint8_t buffer[10];

	buffer[0] = 0x01;
	buffer[1] = g;
	buffer[2] = 0x01;
	buffer[3] = 0x00;
	buffer[4] = 0x01;
	buffer[5] = b;
	buffer[6] = 0x01;
	buffer[7] = r;
	buffer[8] = 0x01;
	buffer[9] = w;

	return gattlib_write_char_by_handle(connection, 0x2a, buffer, sizeof(buffer));
}



int main(int argc, char *argv[]) {
	//uint8_t buffer[10] = {0x01, 0xFF, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x0F};
    gatt_connection_t* connection;
    int ret;
    int c = 0;
    int w = 0;
    int x = 0;
    char up = 1;
    
    
    connection = gattlib_connect(NULL, "00:B4:C5:D1:01:6E", BDADDR_LE_PUBLIC, BT_SEC_LOW, 0, 0);
    


	if (connection == NULL) {
		fprintf(stderr, "Fail to connect to the bluetooth device.\n");
		return 1;
	}

	while(c < 100000){
		x = (int)(w/25.5) % 11;
		ret = set_color(connection, w, 0, 0, x);
		printf("%d-%d\n",w, x);
		fflush(stdout);

		if(up == 1){
			w+=10;
		} else {
			w-=10;
		}

		if(w >= 255){
			w = 255;
			up = 0;
		} else if(w < 1){
			w = 0;
			up = 1;
		}

	}

	//ret = gattlib_write_char_by_handle(connection, 0x2a, buffer, sizeof(buffer));
	assert(ret == 0);


	gattlib_disconnect(connection);
	return 0;
    
}
