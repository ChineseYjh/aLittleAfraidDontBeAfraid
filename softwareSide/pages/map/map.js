
//js
Page(
  {
    data:{
      latitude:0,
      longitude:0,
      //倒计时
      windowHeight: 654,
      maxtime: "",
      isHiddenLoading: true,
      isHiddenToast: true,
      dataList: {},
      countDownDay: 0,
      countDownHour: 0,
      countDownMinute: 0,
      countDownSecond: 0,  
    },
onReady: function() {
  //页面渲染完成
  wx.getLocation({
    success: function (res) {
      console.log(res)
    },
    fail: function () {
      console.log('接口调用失败')
    },
    complete: function () {
      console.log('接口调用完成')
    }
  });
    this.mapContext = wx.createMapContext('theMap');
    
    
    //倒计时
    var totalSecond = 1505540080 - Date.parse(new Date()) / 1000;

    var interval = setInterval(function () {
      // 秒数  
      var second = totalSecond;

      // 天数位  
      var day = Math.floor(second / 3600 / 24);
      var dayStr = day.toString();
      if (dayStr.length == 1) dayStr = '0' + dayStr;

      // 小时位  
      var hr = Math.floor((second - day * 3600 * 24) / 3600);
      var hrStr = hr.toString();
      if (hrStr.length == 1) hrStr = '0' + hrStr;

      // 分钟位  
      var min = Math.floor((second - day * 3600 * 24 - hr * 3600) / 60);
      var minStr = min.toString();
      if (minStr.length == 1) minStr = '0' + minStr;

      // 秒位  
      var sec = second - day * 3600 * 24 - hr * 3600 - min * 60;
      var secStr = sec.toString();
      if (secStr.length == 1) secStr = '0' + secStr;

      this.setData({
        countDownDay: dayStr,
        countDownHour: hrStr,
        countDownMinute: minStr,
        countDownSecond: secStr,
      });
      totalSecond--;
      if (totalSecond < 0) {
        clearInterval(interval);
        wx.showToast({
          title: '活动已结束',
        });
        this.setData({
          countDownDay: '00',
          countDownHour: '00',
          countDownMinute: '00',
          countDownSecond: '00',
        });
      }
    }.bind(this), 1000);
    },
    //cell事件处理函数  
    bindCellViewTap: function (e) {
      var id = e.currentTarget.dataset.id;
      wx.navigateTo({
        url: '../babyDetail/babyDetail?id=' + id
      });  
},
onLoad: function () {
  this.setData({
    windowHeight: wx.getStorageSync('windowHeight')
  });
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
      phoneNumber: getApp().globalData.phoneNumber
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
  