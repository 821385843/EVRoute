//
//  EVListViewController.h
//  EVRoute_Example
//
//  Created by Wei Xie on 2022/11/11.
//  Copyright © 2022 821385843@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef UIViewController *(^ViewControllerHandler)();

@interface EVListViewController : UIViewController

+ (void)registerWithTitle:(NSString *)title handler:(ViewControllerHandler)handler;

@end

NS_ASSUME_NONNULL_END
