//
//  EVRoute.h
//  EVRoute
//
//  Created by 821385843@qq.com on 11/11/2022.
//  Copyright (c) 2022 821385843@qq.com. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const EVRouteParameterURL;
extern NSString *const EVRouteParameterCompletion;
extern NSString *const EVRouteParameterUserInfo;

/**
 *  routerParameters 里内置的几个参数会用到上面定义的 string
 */
typedef void (^EVRouteHandler)(NSDictionary *routerParameters);

@interface EVRoute : NSObject

/**
 *  注册 URLPattern 对应的 Handler，在 handler 中可以初始化 VC，然后对 VC 做各种操作
 *
 *  @param URLPattern 带上 scheme，如 ev://beauty/:id
 *  @param handler    该 block 会传一个字典，包含了注册的 URL 中对应的变量。
 *                    假如注册的 URL 为 ev://beauty/:id 那么，就会传一个 @{@"id": 4} 这样的字典过来
 */
+ (void)registerURLPattern:(NSString *)URLPattern toHandler:(EVRouteHandler)handler;

/**
 *  打开此 URL
 *  会在已注册的 URL -> Handler 中寻找，如果找到，则执行 Handler
 *
 *  @param URL 带 Scheme，如 ev://beauty/3
 */
+ (void)openURL:(NSString *)URL;

/**
 *  打开此 URL，同时当操作完成时，执行额外的代码
 *
 *  @param URL        带 Scheme 的 URL，如 ev://beauty/4
 *  @param completion URL 处理完成后的 callback，完成的判定跟具体的业务相关
 */
+ (void)openURL:(NSString *)URL completion:(void (^)(void))completion;

/// 打开此 URL，带上附加信息，同时当操作完成时，执行额外的代码
/// @param URL 带 Scheme 的 URL，如 ev://beauty/4
/// @param userInfo 附加参数
/// @param completion URL 处理完成后的 callback，完成的判定跟具体的业务相关
+ (void)openURL:(NSString *)URL withUserInfo:(NSDictionary *)userInfo completion:(void (^)(void))completion;

/// 是否可以打开URL
/// @param URL URL
+ (BOOL)canOpenURL:(NSString *)URL;

/**
 *  调用此方法来拼接 urlpattern 和 parameters
 *
 *  #define EV_ROUTE_BEAUTY @"beauty/:id"
 *  [EVRoute generateURLWithPattern:EV_ROUTE_BEAUTY, @[@13]];
 *
 *
 *  @param pattern    url pattern 比如 @"beauty/:id"
 *  @param parameters 一个数组，数量要跟 pattern 里的变量一致
 *
 *  @return
 */
+ (NSString *)generateURLWithPattern:(NSString *)pattern parameters:(NSArray *)parameters;
@end
