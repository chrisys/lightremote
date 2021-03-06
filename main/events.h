void connect_event(const char * payload, size_t length) {
}

void user_connected(const char * payload, size_t length) {
}

void user_disconnected(const char * payload, size_t length) {
}

void notify_change(const char * payload, size_t length) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& change = jsonBuffer.parseObject(payload);

  if(change.success()) {
    // update the state channel with the new info
    int circuit = change["circuit"];
    circuit--;

    const char* change_status = change["status"];
    if(change_status != '\0')
    {
      state_channels[circuit].state = change["status"];
    }
    
    state_channels[circuit].desired_state = change["set"];
  }
}

void notify_message(const char * payload, size_t length) {
}

void update_times(const char * payload, size_t length) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& change = jsonBuffer.parseObject(payload);

  if(change.success()) {
    time_t t = change["ts"];
    int circuit = change["circuit"];
    circuit--;

    if(t>0) {
      state_channels[circuit].timestamp = t;
      state_channels[circuit].timestamp_state = change["status"];
      state_channels[circuit].show_text_time = true;
    } else {
      state_channels[circuit].show_text_time = false;
    }
  }
}

void server_time(const char * payload, size_t length) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& change = jsonBuffer.parseObject(payload);

  if(change.success()) {
    current_time = change["ts"];
    setTime(current_time);
  }
}

// EMITS
void switch_change(switch_channel channel) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& change = jsonBuffer.createObject();
  
  channel.circuit++;
  change["circuit"] = channel.circuit;
  change["set"] = channel.desired_state;

  char outputjson[100];
  change.printTo(outputjson);
  Serial.println(outputjson);
  socket.emit("switch change", outputjson);
}

