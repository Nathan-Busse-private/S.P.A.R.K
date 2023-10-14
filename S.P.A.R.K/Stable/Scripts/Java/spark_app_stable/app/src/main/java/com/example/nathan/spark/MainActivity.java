package com.example.nathan.spark;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Vibrator;
import android.preference.PreferenceActivity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {
    private LinearLayout layout1;
    private RelativeLayout layout2;
    private ListView lv;
    private Switch sw;
    private ToggleButton start, light, brake;
    private Button cancel, up, down, left, right, horn;
    private ProgressBar pb;
    private SeekBar seekBar;
    private TextView tv;
    private int value = 0;

    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private BluetoothAdapter bluetoothAdapter = null;
    private BluetoothSocket btSocket = null;
    private Set<BluetoothDevice> pairedDevices;
    private ConnectedThread mConnectedThread;
    public static String MAC;
    private boolean isConnected = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        layout1 = (LinearLayout) findViewById(R.id.layoutHeader);
        layout2 = (RelativeLayout) findViewById(R.id.layoutMain);
        lv = (ListView) findViewById(R.id.listDevice);
        cancel = (Button) findViewById(R.id.btnCancel);
        sw = (Switch)findViewById(R.id.switch1);
        start = (ToggleButton) findViewById(R.id.btnStart);
        up = (Button) findViewById(R.id.btnUp);
        down = (Button) findViewById(R.id.btnDown);
        left = (Button) findViewById(R.id.btnLeft);
        right = (Button) findViewById(R.id.btnRight);
        horn = (Button) findViewById(R.id.btnHorn);
        light = (ToggleButton) findViewById(R.id.btnLight);
        seekBar = (SeekBar) findViewById(R.id.speedBar);
        brake = (ToggleButton) findViewById(R.id.btnBrake);
        pb = (ProgressBar) findViewById(R.id.pBar);
        pb.getProgressDrawable().setColorFilter(
                Color.rgb(147,191,214), android.graphics.PorterDuff.Mode.SRC_IN);
        tv = (TextView) findViewById(R.id.textView);

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (start.isChecked()) {
                    listDevice();
                } else {
                    disconnect();
                }
            }
        });

        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                int itemPosition = position;
                String address = (String) lv.getItemAtPosition(itemPosition);
                String deviceAddress = address.substring(address.length() - 17);
                connect(address, deviceAddress);
            }
        });

        cancel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                layout1.setVisibility(View.GONE);
                layout2.setVisibility(View.VISIBLE);
                start.setChecked(false);
            }
        });

        buttonWork();

    }

    private void listDevice() {
        pairedDevices = bluetoothAdapter.getBondedDevices();
        ArrayList list = new ArrayList();
        for (BluetoothDevice bt : pairedDevices)
            list.add(bt.getName() + "\n" + bt.getAddress());
        ;
        final ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, list);
        lv.setAdapter(adapter);
        layout2.setVisibility(View.GONE);
        layout1.setVisibility(View.VISIBLE);
    }

    private void connect(String address, String deviceAddress) {
        BluetoothDevice device = bluetoothAdapter.getRemoteDevice(deviceAddress);
        try {
            btSocket = createBluetoothSocket(device);
        } catch (IOException e1) {
            printMsg("Fatal Error" + "," + "In onResume() and socket create failed: ");
        }
        bluetoothAdapter.cancelDiscovery();
        try {
            btSocket.connect();
            isConnected = true;
            printMsg("Connected to: " + address);
            layout1.setVisibility(View.GONE);
            layout2.setVisibility(View.VISIBLE);
            pb.setProgress(100);
        } catch (IOException e) {
            try {
                btSocket.close();
            } catch (IOException e2) {
                printMsg("Fatal Error: In onResume() and unable to close socket during connection failure");
            }
        }
        mConnectedThread = new ConnectedThread(btSocket);
        mConnectedThread.start();
        mConnectedThread.write("S");
    }


    private void buttonWork(){
        sw.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(sw.isChecked()){
                    writeData("E");
                }
                else{
                    writeData("Z");
                }
            }
        });

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                //tv.setText("Pivot angle " + (2* progress )* 5.5 + "°");
                switch (progress) {
                    case 0:
                       // tv.setText("Pivot angle " + 7* progress  + "°");

                        writeData("0");
                        tv.setText("Pivot angle " + 7 +progress  + "°      ( Left )");

                        break;
                    case 1:
                        writeData("1");
                        tv.setText("Pivot angle " + 74* progress  + "°      ( Left )");

                        break;
                    case 2:
                        writeData("2");
                        tv.setText("Pivot angle " + 39* progress  + "°      ( Left )");

                        break;
                    case 3:
                        writeData("3");
                        tv.setText("Pivot angle " + 27.333333333333333* progress  + "°      ( Left )");

                        break;
                    case 4:
                        writeData("4");
                        tv.setText("Pivot angle " + 21.5* progress  + "°      ( Left )");

                        break;
                    case 5:
                        writeData("5");
                        tv.setText("Pivot angle " + 18* progress  + "°  ( Flat angle )");

                        break;
                    case 6:
                        writeData("6");
                        tv.setText("Pivot angle " + 15.666666666666666* progress  + "°      ( Right )");

                        break;
                    case 7:
                        writeData("7");
                        tv.setText("Pivot angle " + 14* progress  + "°      ( Right )");

                        break;
                    case 8:
                        writeData("8");
                        tv.setText("Pivot angle " + 12.75* progress  + "°      ( Right )");

                        break;
                    case 9:
                        writeData("9");
                        tv.setText("Pivot angle " + 11.7777777777777777* progress  + "°      ( Right )");

                        break;
                    case 10:
                        writeData("q");
                        tv.setText("Pivot angle " + 11* progress  + "°      ( Right )");

                        break;
                    default:
                        writeData("~");
                        tv.setText("Pivot angle " + 18* progress  + "°  ( Flat angle )");
                        break;
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        up.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    up.setBackgroundResource(R.drawable.arrow_up);
                    writeData("F");
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    writeData("S");
                    up.setBackgroundResource(R.drawable.arrow_up0);
                }
                return false;
            }
        });

        down.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    down.setBackgroundResource(R.drawable.arrow_down);
                    writeData("B");
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    writeData("S");
                    down.setBackgroundResource(R.drawable.arrow_down0);
                }
                return false;
            }
        });

        left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    left.setBackgroundResource(R.drawable.arrow_left);
                    writeData("L");
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    writeData("S");
                    left.setBackgroundResource(R.drawable.arrow_left0);
                }
                return false;
            }
        });

        right.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    right.setBackgroundResource(R.drawable.arrow_right);
                    writeData("R");
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    writeData("S");
                    right.setBackgroundResource(R.drawable.arrow_right0);
                }
                return false;
            }
        });

        brake.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (brake.isChecked()) {
                    writeData("W");
                } else {
                    writeData("Z");
                }
            }
        });

        horn.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    String url = "https://github.com/Nathan-Busse";
                    Uri uri = Uri.parse(url);
                    Intent intent = new Intent(Intent.ACTION_VIEW, uri);
                    // Verify that the intent will resolve to an activity
                    if (intent.resolveActivity(getPackageManager()) != null) {
                        // Here we use an intent without a Chooser unlike the next example
                        startActivity(intent);
                    }
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    horn.setBackgroundResource(R.drawable.horn0);
                }
                return false;
            }
        });

        light.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(light.isChecked()){
                    writeData("Z");
                }
                else{
                    writeData("S");
                }
            }
        });
    }

    private void writeData(String s) {
        if(isConnected){
            mConnectedThread.write(s);
        }
        else{
            ((Vibrator)getSystemService(VIBRATOR_SERVICE)).vibrate(200);
        }
    }

    private void printMsg(String msg) {
        Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show();
    }

    private void disconnect() {
        if (btSocket.isConnected())
        {
            try
            {
                pb.setProgress(0);
                btSocket.close();
                isConnected = false;
                printMsg("Disconnected");
            }
            catch (IOException e)
            {
                printMsg("Error !!!");
            }
        }
    }

    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
        return device.createRfcommSocketToServiceRecord(MY_UUID);
    }

    private class ConnectedThread extends Thread {
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {
            OutputStream tmpOut = null;
            try {
                tmpOut = socket.getOutputStream();
            }
            catch (IOException e) {
                printMsg("Error output!!!");
            }
            mmOutStream = tmpOut;
        }

        public void write(String input) {
            byte[] msgBuffer = input.getBytes();
            if(isConnected){
                try {
                    mmOutStream.write(msgBuffer);
                } catch (IOException e) {
                    printMsg("Connection Failure");
                }
            }
        }
    }

}