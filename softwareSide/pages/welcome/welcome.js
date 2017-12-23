Page({

  data: {
    opacity: 0.4,
    disabled: true,
        rule: 'up',
          phoneNum1:"",
          imageSrc:"../../images/avatar/avatar-7.jpg"
  },
  onTapJump: function (event) {
  wx.redirectTo({    
    /*三种方法之一，用来实现跳转页面*/
      /*wx.redirectTo关闭当前页面，无法返回
      wx.navigateTo隐藏当前页面，可以返回*/
      url: "../post/post",
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
    },/*tap操作的事件处理函数*/
      onUnload: function (event) {
        console.log("page is unload")
      },
      onHide: function (event) {
        console.log("page is hide")
      },
     
      
      change: function (e) {
        //当有输入时激活发送按钮，无输入则禁用按钮
        var this_=this;
        if (e.detail.value != "") {
          this.setData({
            opacity: 1,
            disabled: false,
            phoneNum1:e.detail.value
          });
          getApp().globalData.phoneNumber =this_. data.phoneNum1;
          }
          else {
          this.setData({
            phoneNum1: "",
            opacity: 0.4,
            disabled: true,
          });
        }
      },


    })
  
