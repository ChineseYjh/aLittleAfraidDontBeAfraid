
//倒计时
// indes.js
/** 
 * 需要一个目标日期，初始化时，先得出到当前时间还有剩余多少秒
 * 1.将秒数换成格式化输出为XX天XX小时XX分钟XX秒 XX
 * 2.提供一个时钟，每10ms运行一次，渲染时钟，再总ms数自减10
 * 3.剩余的秒次为零时，return，给出tips提示说，已经截止
 */

// 定义一个总毫秒数，以一天为例
// var total_micro_second = 3600 * 1000*24;//这是一天倒计时

Page(
  {
    data:{
      map_width: 380,
      map_height: 300,
      latitude:0,
      longitude:0,
      clock: ''
    },
onReady: function() {
  //页面渲染完成
    this.mapContext = wx.createMapContext('theMap');
},
onLoad: function () {
  var this_=this;
  wx.getLocation({
    type: 'gcj02',
    success: function (res) {
      this_.setData(
        {
          latitude: res.latitude,
          longitude: res.longitude,
          //speed:res.speed,
        }
      )
      console.log(res)
    },
    fail: function (res) {
      console.log("fail")
    },
    complete: function (res) {
      console: log("end")
    }
  });
 },
tapToCount:function()
{
  var total_micro_second = 1000 * (parseInt(getApp().globalData.Time) * 60 * 60 + parseInt(getApp().globalData.Time.substring(3, 5)) * 60);//这是倒计时
  /* 毫秒级秒杀倒计时 */
  function countdown(that) {
    // 渲染倒计时时钟
    that.setData({
      clock: dateformat(total_micro_second)//格式化时间
    });

    if (total_micro_second <= 0) {
      that.setData({
        clock: "保护时间已到！"
      });
      wx.getLocation({
        type: 'gcj02',
        success: function (res) {
          that.setData(
            {
              latitude: res.latitude,
              longitude: res.longitude,
              //speed:res.speed,
            }
          )
          console.log(res)
        },
        fail: function (res) {
          console.log("fail")
        },
        complete: function (res) {
          console: log("end")
        }
      });
      wx.request({
        url: "https://api.heclouds.com/devices/20452006/datapoints?type=3",
        header: {
          'content-type': 'application/json',
          'api-key': 'I0eB3CJjGR9VhUTAhLrnww14TSE='
        },
        data: {
          latitude: that.data.latitude,
          longitude: that.data.longitude,
          //speed:this_.data.speed,
          phoneNumber: getApp().globalData.phoneNumber,
          ThisIsAWorkByChineseYjhsTeam:''
        },
        method: 'POST',
        success: function (res) {
          console.log(res);
        },
        fail: function (res) {
          console.log("fail!")
        },
        complete: function (res) {
          console.log("end")
        }
      });
      wx.redirectTo({
        /*三种方法之一，用来实现跳转页面*/
        /*wx.redirectTo关闭当前页面，无法返回
        wx.navigateTo隐藏当前页面，可以返回*/
        url: "../../pages/alarm/alarm",
        success: function () {
          console.log("jump success")
        },
        fail: function () {
          console.log("jump failed")
        },
        complete: function () {
          console.log("jump complete")
        }
      });
      // timeout则跳出递归
      return;
    }

    //settimeout实现倒计时效果
    setTimeout(function () {
      // 放在最后--
      total_micro_second -= 10;
      countdown(that);
    }
      , 10)//注意毫秒的步长受限于系统的时间频率，于是我们精确到0.01s即10ms
  }

  // 时间格式化输出，如1天天23时时12分分12秒秒12 。每10ms都会调用一次
  function dateformat(micro_second) {
    // 总秒数
    var second = Math.floor(micro_second / 1000);
    // 天数
    var day = Math.floor(second / 3600 / 24);
    // 总小时
    var hr = Math.floor(second / 3600);
    // 小时位
    var hr2 = hr % 24;
    // 分钟位
    var min = Math.floor((second - hr * 3600) / 60);
    // 秒位
    var sec = (second - hr * 3600 - min * 60);// equal to => var sec = second % 60;
    // 毫秒位，保留2位
    var micro_sec = Math.floor((micro_second % 1000) / 10);
    return hr2 + "时" + min + "分" + sec + "秒" + micro_sec;
  }
  countdown(this);
},
moveToLocation:function()
{
  this.mapContext.moveToLocation();
},
openChoseLocationFun: function() {
  wx.chooseLocation({
    success: function (res) {
      console.log('调用地图位置成功，', res)
    },
    cancel: function () {
      console.log('用户取消选择位置')
    },
    fail: function () {
      console.log('地图选择失败')
    },
    complete:function()
    {
      console.log('end')
    }
  })
},
tapToAlarm:function()
{
  var this_ = this;
  wx.getLocation({
    type: 'gcj02',
    success: function (res) {
      this_.setData(
        {
          latitude: res.latitude,
          longitude: res.longitude,
          //speed:res.speed,
        }
      )
      console.log(res)
    },
    fail: function (res) {
      console.log("fail")
    },
    complete: function (res) {
      console: log("end")
    }
  });
  wx.request({
    url: "https://api.heclouds.com/devices/20452006/datapoints?type=3",
    header: {
      'content-type': 'application/json',
      'api-key': 'I0eB3CJjGR9VhUTAhLrnww14TSE='
    },
    data: {
      latitude: this_.data.latitude,
      longitude: this_.data.longitude,
      //speed:this_.data.speed,
      phoneNumber: getApp().globalData.phoneNumber,
      ThisIsAWorkByChineseYjhsTeam:''
    },
    method: 'POST',
    success: function (res) {
      console.log(res);
    },
    fail: function (res) {
      console.log("fail!")
    },
   complete: function (res) {
     console.log("end")
    }
})}
  })