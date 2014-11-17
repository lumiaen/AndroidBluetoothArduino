package com.coolandkasparof.androidbluetootharduino;
import android.os.Bundle;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Toast;

import java.util.concurrent.TimeUnit;

import app.akexorcist.bluetoothspp.BluetoothSPP;
import app.akexorcist.bluetoothspp.BluetoothSPP.BluetoothConnectionListener;
import app.akexorcist.bluetoothspp.BluetoothSPP.OnDataReceivedListener;
import app.akexorcist.bluetoothspp.BluetoothState;
import app.akexorcist.bluetoothspp.DeviceList;



public class MainActivity extends Activity {
    public String speed="150";
    BluetoothSPP bt;
    private TextView text;
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        text = (TextView) findViewById(R.id.text);
        bt = new BluetoothSPP(this);

        if(!bt.isBluetoothAvailable()) {
                    text.setText("Bluetooth is not available");
            finish();
        }

        bt.setOnDataReceivedListener(new OnDataReceivedListener() {
            public void onDataReceived(byte[] data, String message) {
                Toast.makeText(MainActivity.this, message, Toast.LENGTH_SHORT).show();
            }
        });

        bt.setBluetoothConnectionListener(new BluetoothConnectionListener() {
            public void onDeviceConnected(String name, String address) {
                text.setText("Connected to " + name + "\n" + address);
                }

            public void onDeviceDisconnected() {
                text.setText("Connection lost");
            }

            public void onDeviceConnectionFailed() {
                text.setText("Unable to connect");
            }
        });

        Button btnConnect = (Button)findViewById(R.id.btnConnect);
        btnConnect.setOnClickListener(new OnClickListener(){
            public void onClick(View v){
                if(bt.getServiceState() == BluetoothState.STATE_CONNECTED) {
                    bt.disconnect();
                } else {
                    Intent intent = new Intent(getApplicationContext(), DeviceList.class);
                    startActivityForResult(intent, BluetoothState.REQUEST_CONNECT_DEVICE);
                }
            }
        });
    }

    public void onDestroy() {
        super.onDestroy();
        bt.stopService();
    }

    public void onStart() {
        super.onStart();
        if (!bt.isBluetoothEnabled()) {
            Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(intent, BluetoothState.REQUEST_ENABLE_BT);
        } else {
            if(!bt.isServiceAvailable()) {
                bt.setupService();
                bt.startService(BluetoothState.DEVICE_OTHER);
                setup();
            }
        }
    }

    public void setup() {
        final Button fwd = (Button)findViewById(R.id.forward);
        fwd.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View fwd, MotionEvent theMotion) {

                switch ( theMotion.getAction() ) {
                    case MotionEvent.ACTION_DOWN:
                        bt.send("*f"+speed, false);
                        break;
                    case MotionEvent.ACTION_UP:
                        bt.send("*f000", false);
                        break;
                }
                return true;
            }
        });


       final Button  bck = (Button)findViewById(R.id.back);
        bck.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View bck, MotionEvent theMotion) {

                switch (theMotion.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        bt.send("*b"+speed, false);
                        break;
                    case MotionEvent.ACTION_UP:
                        bt.send("*b000", false);
                        break;
                }
                return true;
            }
        });

        final Button lft = (Button)findViewById(R.id.left);
        lft.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View lft, MotionEvent theMotion) {

                switch ( theMotion.getAction() ) {
                    case MotionEvent.ACTION_DOWN:
                        bt.send("*l", false);
                        break;
                    case MotionEvent.ACTION_UP:
                        bt.send("*s", false);
                        break;
                }
                return true;
            }
        });

        final Button rgt = (Button)findViewById(R.id.right);
        rgt.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View rgt, MotionEvent theMotion) {

                switch ( theMotion.getAction() ) {
                    case MotionEvent.ACTION_DOWN:
                        bt.send("*r", false);
                        break;
                    case MotionEvent.ACTION_UP:
                        bt.send("*s", false);
                        break;
                }
                return true;
            }
        });
        final CheckBox low = (CheckBox)findViewById(R.id.low);
        final CheckBox medium = (CheckBox)findViewById(R.id.medium);
        final CheckBox high = (CheckBox)findViewById(R.id.high);
        low.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton low, boolean isChecked) {
            if (isChecked){
                medium.setChecked(false);
                high.setChecked(false);
                speed="150";
            }else{
                if (!medium.isChecked()&&!high.isChecked()){
                    low.setChecked(true);
                    speed="150";
                }
            }
            }
        });
        medium.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton medium, boolean isChecked) {
                if (isChecked){
                    low.setChecked(false);
                    high.setChecked(false);
                    speed="200";
                }else{
                    if (!low.isChecked()&&!high.isChecked()){
                        medium.setChecked(true);
                        speed="200";
                    }
                }
            }
        });
        high.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton high, boolean isChecked) {
                if (isChecked){
                    medium.setChecked(false);
                    low.setChecked(false);
                    speed="255";
                }else{
                    if (!medium.isChecked()&&!low.isChecked()){
                        high.setChecked(true);
                        speed="255";
                    }
                }
            }
        });
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == BluetoothState.REQUEST_CONNECT_DEVICE) {
            if(resultCode == Activity.RESULT_OK)
                bt.connect(data);
        } else if(requestCode == BluetoothState.REQUEST_ENABLE_BT) {
            if(resultCode == Activity.RESULT_OK) {
                bt.setupService();
                bt.startService(BluetoothState.DEVICE_OTHER);
                setup();
            } else {
                text.setText("Bluetooth was not enabled.");
                finish();
            }
        }
    }

}
