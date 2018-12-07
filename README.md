generic grbl message parser based on work by Terje Io

https://github.com/terjeio/GRBL_MPG_DRO_BoosterPack


Currently working with grbl 1.1f


main usage is to call parseData( char * serial_line_data), this will update the grbl_data struct with any changes and the values of those changes.

to get the current pointer to the state structure call getData()

if simply waiting for a state change you can call grblParseState (char *  new_message,grbl_data_t * current_state).  if it returns true the state has changed



