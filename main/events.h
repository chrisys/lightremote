void user_connected(const char * payload, size_t length) {
  Serial.println(payload);
}

void user_disconnected(const char * payload, size_t length) {
  Serial.println(payload);
}

void notify_change(const char * payload, size_t length) {
  Serial.println(payload);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& change = jsonBuffer.parseObject(payload);

  if(change.success()) {
    // update the state channel with the new info
    int circuit = change["circuit"];
    circuit--;

    const char* change_status = change["status"];
    if(change_status != "")
    {
      Serial.println(change_status);
      // TODO fix bug here as null response in json is setting status to false instead of leaving as is
      state_channels[circuit].state = change["status"];
    }
    
    state_channels[circuit].desired_state = change["set"];
  }
}

void notify_message(const char * payload, size_t length) {
  Serial.println(payload);
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
