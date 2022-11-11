# EVRoute
一个高效/灵活的 iOS URL Router

## 安装

```
pod 'EVRoute', '~>1.0.0'
```

## 使用姿势

### 最基本的使用

```objc
[EVRoute registerURLPattern:@"ev://foo/bar" toHandler:^(NSDictionary *routerParameters) {
    NSLog(@"routerParameterUserInfo:%@", routerParameters[EVRouteParameterUserInfo]);
}];

[EVRoute openURL:@"ev://foo/bar"];
```

当匹配到 URL 后，`routerParameters` 会自带几个 key

```objc
extern NSString *const EVRouteParameterURL;
extern NSString *const EVRouteParameterCompletion;
extern NSString *const EVRouteParameterUserInfo;
```

### 处理中文也没有问题

```objc
[EVRoute registerURLPattern:@"ev://category/家居" toHandler:^(NSDictionary *routerParameters) {
    NSLog(@"routerParameters:%@", routerParameters);
}];

[EVRoute openURL:@"ev://category/家居"];
```

### Open 时，可以传一些 userinfo 过去

```objc
[EVRoute registerURLPattern:@"ev://category/travel" toHandler:^(NSDictionary *routerParameters) {
    NSLog(@"routerParameters[EVRouteParameterUserInfo]:%@", routerParameters[EVRouteParameterUserInfo]);
    // @{@"user_id": @1900}
}];

[EVRoute openURL:@"ev://category/travel" withUserInfo:@{@"user_id": @1900} completion:nil];
```

### 如果有可变参数（包括 URL Query Parameter）会被自动解析

```objc
[EVRoute registerURLPattern:@"ev://search/:query" toHandler:^(NSDictionary *routerParameters) {
    NSLog(@"routerParameters[query]:%@", routerParameters[@"query"]); // bicycle
    NSLog(@"routerParameters[color]:%@", routerParameters[@"color"]); // red
}];

[EVRoute openURL:@"ev://search/bicycle?color=red"];
```

### 定义一个全局的 URL Pattern 作为 Fallback

```objc
[EVRoute registerURLPattern:@"ev://" toHandler:^(NSDictionary *routerParameters) {
    NSLog(@"没有人处理该 URL，就只能 fallback 到这里了");
}];
    
[EVRoute openURL:@"ev://search/travel/china?has_travelled=0"];
```

### 当 Open 结束时，执行 Completion Block

```objc
[EVRoute registerURLPattern:@"ev://detail" toHandler:^(NSDictionary *routerParameters) {
    NSLog(@"匹配到了 url, 一会会执行 Completion Block");
    
    // 模拟 push 一个 VC
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.25 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        void (^completion)() = routerParameters[EVRouteParameterCompletion];
        if (completion) {
            completion();
        }
    });
}];

[EVRoute openURL:@"ev://detail" withUserInfo:nil completion:^{
    [self appendLog:@"Open 结束，我是 Completion Block"];
}];
```

### 生成 URL

URL 的处理一不小心，就容易散落在项目的各个角落，不容易管理。比如注册时的 pattern 是 `ev://beauty/:id`，然后 open 时就是 `ev://beauty/123`，这样到时候 url 有改动，处理起来就会很麻烦，不好统一管理。

所以 EVRoute 提供了一个类方法来处理这个问题。

```objc
+ (NSString *)generateURLWithPattern:(NSString *)pattern parameters:(NSArray *)parameters;
```

使用方式

```objc
#define TEMPLATE_URL @"ev://search/:keyword"
    
[EVRoute registerURLPattern:TEMPLATE_URL  toHandler:^(NSDictionary *routerParameters) {
    NSLog(@"routerParameters[keyword]:%@", routerParameters[@"keyword"]); // Hangzhou
}];

[EVRoute openURL:[EVRoute generateURLWithPattern:TEMPLATE_URL parameters:@[@"Hangzhou"]]];
}
```

这样就可以在一个地方定义所有的 URL Pattern，使用时，用这个方法生成 URL 就行了。


## 协议

EVRoute 被许可在 MIT 协议下使用。查阅 LICENSE 文件来获得更多信息。
