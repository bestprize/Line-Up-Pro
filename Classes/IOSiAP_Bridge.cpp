//
//  IOSiAP_Bridge.cpp
//  LongChengDaRen
//
//  Created by 白白 on 14-11-11.
//
//

#include "IOSiAP_Bridge.h"
#include "Purchase.h"
#include "cocos2d.h"
#include <iostream>
#include <vector>
USING_NS_CC;
using namespace std;

IOSiAP_Bridge::IOSiAP_Bridge()
{
    iap = new IOSiAP();
    iap->delegate = this;
}

IOSiAP_Bridge::~IOSiAP_Bridge()
{
    delete iap;
}

void IOSiAP_Bridge:: requestProducts(int id)
{
    productID = id;
    vector<std::string> product;
    product.push_back("consumable001");
    product.push_back("consumable002");
    product.push_back("consumable005");
    product.push_back("consumable0010");
    product.push_back("consumable0050");
    //把需要付费的道具的所有product id都放到容器里面传进去
    iap->requestProducts(product);
}

void IOSiAP_Bridge::onRequestProductsFinish(void)
{
    std::string identifier = "";
    switch (productID) {
        case 1:
            identifier = "consumable001";
            break;
        case 2:
            identifier = "consumable002";
            break;
        case 3:
            identifier = "consumable005";
            break;
        case 4:
            identifier = "consumable0010";
            break;
        case 5:
            identifier = "consumable0050";
            break;
        default:
            break;
    }

    //必须在onRequestProductsFinish后才能去请求iAP产品数据。
    IOSProduct *product = iap->iOSProductByIdentifier(identifier);
    // 然后可以发起付款请求。,第一个参数是由iOSProductByIdentifier获取的IOSProduct实例，第二个参数是购买数量
    iap->paymentWithProduct(product, 1);
    
}

void IOSiAP_Bridge::onRequestProductsError(int code)
{
    //这里requestProducts出错了，不能进行后面的所有操作。
    log("付款失败");
}

void IOSiAP_Bridge::onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity)
{
    
    if (event == IOSIAP_PAYMENT_PURCHAED) {
        //付款成功了，可以吧金币发给玩家了。
		//根据传入的参数就能知道购买的是哪种类型的金币
        switch (productID) {
            case 1:
            {
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                UserDefault::sharedUserDefault()->setIntegerForKey("wealth",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0)+100);
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                auto *newPurchaseScene = Purchase::createScene();
                Director::sharedDirector()->replaceScene(newPurchaseScene);
                break;
            }
            case 2:
            {
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                UserDefault::sharedUserDefault()->setIntegerForKey("wealth",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0)+210);
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                auto *newPurchaseScene = Purchase::createScene();
                Director::sharedDirector()->replaceScene(newPurchaseScene);
                break;
            }
            case 3:
            {
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                UserDefault::sharedUserDefault()->setIntegerForKey("wealth",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0)+600);
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                auto *newPurchaseScene = Purchase::createScene();
                Director::sharedDirector()->replaceScene(newPurchaseScene);
                break;
            }
            case 4:
            {
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                UserDefault::sharedUserDefault()->setIntegerForKey("wealth",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0)+1300);
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                break;
            }
            case 5:
            {
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                UserDefault::sharedUserDefault()->setIntegerForKey("wealth",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0)+7500);
                log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
                auto *newPurchaseScene = Purchase::createScene();
                Director::sharedDirector()->replaceScene(newPurchaseScene);
                break;
            }
            default:
                break;
        }        
        log("付款成功");
        
    }
    //其他状态依情况处理掉。
}
