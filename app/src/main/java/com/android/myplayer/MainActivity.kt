package com.android.myplayer

import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.android.myplayer.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private var myPlayer: MyPlayer? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        myPlayer = MyPlayer()
        //myPlayer?.setDataSource("rtmp://ns8.indexforce.com/home/mystream")
        myPlayer?.setDataSource("rtmp://10.110.3.50:8899/live")

        myPlayer?.setOnPrepareListener {
            runOnUiThread {
                Toast.makeText(this@MainActivity, "可以开始播放了", Toast.LENGTH_LONG).show()
            }
        }
        binding.btPlay.setOnClickListener {
            // 播放前的准备
            myPlayer?.prepare()
        }
    }
}