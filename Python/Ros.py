import rospy
import rospkg
from gazebo_msgs.srv import GetModelState
from gazebo_msgs.msg import ModelState
from gazebo_msgs.srv import SetModelState
import paho.mqtt.client as mqtt
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("fypnam/test",0)

# The callback for when a PUBLISH message is received from the server.

def on_disconnect(client, userdata,rc=0):
    client.loop_stop()

client = mqtt.Client()
client.on_connect = on_connect

client.connect("broker.mqttdashboard.com", 1883, 60)

def set_item(goal_x, goal_y,goal_z,goal_w,objeto):
        state_msg = ModelState()
        state_msg.model_name = objeto
        state_msg.pose.position.x = 0
        state_msg.pose.position.y = 0
        state_msg.pose.position.z = 0
        state_msg.pose.orientation.x = goal_x
        state_msg.pose.orientation.y = goal_y
        state_msg.pose.orientation.z = goal_z
        state_msg.pose.orientation.w = goal_w

        rospy.wait_for_service('/gazebo/set_model_state')
        try:
            set_state = rospy.ServiceProxy(
                '/gazebo/set_model_state', SetModelState)
            resp = set_state(state_msg)
            print(state_msg)

        except rospy.ServiceException:
            print("Service call failed")

def on_message(client, userdata, msg):
    print(msg.payload)
    str_msg = msg.payload.decode('UTF-8')
    angles = str_msg.split(',')
    set_item(float(angles[0]),float(angles[1]),float(angles[2]),"unit_box")
    print(str_msg)

rospy.init_node('usv_simple_ctrl', anonymous=True)
print("rate start")
rate = rospy.Rate(60)
print("stop")
client.on_message = on_message

client.loop_forever()
print("done")