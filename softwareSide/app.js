
  App({
  onLaunch: function () {
    var storageData = wx.getStorageSync('postList');
    if (!storageData) {
      var dataObj = require("data/data.js")
      wx.clearStorageSync();
      wx.setStorageSync('postList', dataObj.postList);
    }
    this._getUserInfo();
    // wx.login();
  },
    _getUserInfo: function () {
      var userInfoStorage = wx.getStorageSync('user');
      if (!userInfoStorage) {
        var that = this;
        wx.login({
          success: function () {
            wx.getUserInfo({
              success: function (res) {
                console.log(res);
                that.globalData.g_userInfo = res.userInfo
                wx.setStorageSync('user', res.userInfo)
              },
              fail: function (res) {
                console.log(res);
              }
            })
          }
        })
      }
      else {
        this.globalData.g_userInfo = userInfoStorage;
      }
    },

  /**
   * 当小程序初始化完成时，会触发 onLaunch（全局只触发一次）
   */
  onLaunch: function () {
    console.log('App.onLaunch()');
  },

  /**
   * 当小程序启动，或从后台进入前台显示，会触发 onShow
   */
  onShow: function (options) {
    
  },

  /**
   * 当小程序从前台进入后台，会触发 onHide
   */
  onHide: function () {
    
  },

  /**
   * 当小程序发生脚本错误，或者 api 调用失败时，会触发 onError 并带上错误信息
   */
  onError: function (msg) {
    
  },
  globalData:{
    phoneNumber:'',
    Time:"00:00",
    ThisIsAWorkByChineseYjhsTeam:''
  }
})
