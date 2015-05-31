#import <UIKit/UIKit.h>
#import "GoogleMobileAds/GADInterstitial.h"

@class RootViewController;

//@interface AppController : NSObject <UIApplicationDelegate> {
//    UIWindow *window;
//}

//@property(nonatomic, readonly) RootViewController* viewController;

@interface AppController : NSObject <UIApplicationDelegate,GADInterstitialDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADInterstitial *interstitial_;
}
@property(nonatomic, retain) GADInterstitial *interstitial;

- (void)showInterstitial;

@end

