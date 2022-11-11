//
//  EVListViewController.m
//  EVRoute_Example
//
//  Created by Wei Xie on 2022/11/11.
//  Copyright © 2022 821385843@qq.com. All rights reserved.
//

#import "EVListViewController.h"

static NSMutableDictionary *titleWithHandlers;
static NSMutableArray *titles;

@interface EVListViewController () <UITableViewDataSource, UITableViewDelegate>
@property (nonatomic) UITableView *tableView;
@end

@implementation EVListViewController

+ (void)registerWithTitle:(NSString *)title handler:(UIViewController *(^)())handler
{
    if (!titleWithHandlers) {
        titleWithHandlers = [[NSMutableDictionary alloc] init];
        titles = [NSMutableArray array];
    }
    [titles addObject:title];
    titleWithHandlers[title] = handler;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.title = @"EVRouteDemo";
    
    self.tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStyleGrouped];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"cell"];
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    [self.view addSubview:self.tableView];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return titleWithHandlers.allKeys.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    cell.textLabel.text = titles[indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    UIViewController *viewController = ((ViewControllerHandler)titleWithHandlers[titles[indexPath.row]])();
    [self.navigationController pushViewController:viewController animated:YES];
}

@end
