
Page({
        data:
        {
          time:'00:00',
          starttime:'00:00',
          endtime:'24:00',
          latitude:0,
          longitude:0,
          //speed:0,
        },//跳转到地图页
        selectchange:function(e)
        {
          console.log(e)
          this.setData(
            {
              time:e.detail.value
            }
          )
        },

tapToAlarm:function()
{
  var this_=this;
  wx.getLocation({
    type: 'gcj02',
    success: function(res) {
      this_.setData(
        {
          latitude:res.latitude,
          longitude:res.longitude,
          //speed:res.speed,
        }
      )
      console.log(res)
    },
    fail:function(res){
    console.log("fail")
    },
    complete:function(res){
    console:log("end")
    }
  });
  wx.request({
    url: "https://api.heclouds.com/devices/20452006/datapoints?type=3",
    header:{
      'content-type':'application/json',
      'api-key':'I0eB3CJjGR9VhUTAhLrnww14TSE='
    },
    data:{
      latitude:this_.data.latitude,
      longitude:this_.data.longitude,
      //speed:this_.data.speed,
      phoneNumber:getApp().globalData.phoneNumber
    },
    method:'POST',
    success:function(res)
    {
      console.log(res);
    },
    fail:function(res)
    {
      console.log("fail!")
    },
    complete:function(res)
    {
      console.log("end")
    }
  })
},

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})
