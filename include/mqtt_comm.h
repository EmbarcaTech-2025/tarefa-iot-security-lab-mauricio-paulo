#ifndef MQTT_COMM_H
#define MQTT_COMM_H
void mqtt_setup(const char *client_id, const char *broker_ip, const char *user, const char *pass, void* cb1, void* cb2);
void mqtt_comm_publish(const char *topic, const uint8_t *data, size_t len);
void subscribe_to_topic(const char *topic, int sub);
void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
#endif