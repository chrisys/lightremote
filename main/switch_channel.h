struct switch_channel {
  int8_t circuit;
  String circuit_string;
  int16_t start_x;
  int16_t start_y; 
  boolean state;
  boolean desired_state;
  boolean show_text_time;
  time_t timestamp;
  boolean timestamp_state;
};

const int channel_count = 5;
switch_channel display_channels[channel_count];
switch_channel state_channels[channel_count];

switch_channel setup_channel(int channel_number) {
  switch_channel new_channel;
  
  switch(channel_number) {
    case 0:
      new_channel.circuit = 0;
      new_channel.start_x = 0;
      new_channel.start_y = 0;
      new_channel.circuit_string = "Circuit 1";
    break;
    case 1:
      new_channel.circuit = 1;
      new_channel.start_x = 121;
      new_channel.start_y = 0;
      new_channel.circuit_string = "Circuit 2";
    break;
    case 2:
      new_channel.circuit = 2;
      new_channel.start_x = 0;
      new_channel.start_y = 107;
      new_channel.circuit_string = "Circuit 3";
    break;
    case 3:
      new_channel.circuit = 3;
      new_channel.start_x = 0;
      new_channel.start_y = 214;
      new_channel.circuit_string = "Cube";
    break;
    case 4:
      new_channel.circuit = 4;
      new_channel.start_x = 121;
      new_channel.start_y = 214;
      new_channel.circuit_string = "School";
    break;
  }

  new_channel.state = false;
  new_channel.desired_state = false;
  new_channel.show_text_time = false;

  return new_channel;
}

boolean compare_state(int channel_number) {
  // take the channel number and compare the one in display to the one in state
  // true = equal
  // false = not equal
  if(display_channels[channel_number].circuit_string != state_channels[channel_number].circuit_string) {
    return false;
  }

  if(display_channels[channel_number].start_x != state_channels[channel_number].start_x) {
    return false;
  }

  if(display_channels[channel_number].start_y != state_channels[channel_number].start_y) {
    return false;
  }
  
  if(display_channels[channel_number].state != state_channels[channel_number].state) {
    return false;
  }

  if(display_channels[channel_number].desired_state != state_channels[channel_number].desired_state) {
    return false;
  }

  if(display_channels[channel_number].timestamp != state_channels[channel_number].timestamp) {
    return false;
  }

  if(display_channels[channel_number].timestamp_state != state_channels[channel_number].timestamp_state) {
    return false;
  }

  if(display_channels[channel_number].show_text_time != state_channels[channel_number].show_text_time) {
    return false;
  }

  return true;
}

void initialise_channels() {
  for(int i=0; i<channel_count; i++) {
    //display_channels[i] = setup_channel(i+1);
    state_channels[i] = setup_channel(i);
  }
}

