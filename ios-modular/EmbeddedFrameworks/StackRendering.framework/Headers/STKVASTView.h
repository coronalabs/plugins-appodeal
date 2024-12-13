//
//  STKVASTView.h
//  StackVASTKit
//
//  Created by Ilia Lozhkin on 14.10.2021.
//

#import <UIKit/UIKit.h>
#import <StackRendering/STKVASTControllerConfiguration.h>


NS_ASSUME_NONNULL_BEGIN

@class STKVASTView;

@protocol STKVASTViewDelegate <NSObject>

- (void)vastViewReady:(STKVASTView *)view;

- (void)vastView:(STKVASTView *)view didFailToLoad:(NSError *)error;

- (void)vastViewDidPresent:(STKVASTView *)view;

- (void)vastViewDidFinish:(STKVASTView *)view;

- (void)vastViewWillLeaveApplication:(STKVASTView *)view;

- (void)vastViewWillPresentProductScreen:(STKVASTView *)view;

- (void)vastViewDidDismissProductScreen:(STKVASTView *)view;

@end

@protocol STKVASTViewDataSources <NSObject>

- (nullable UIViewController *)rootViewControllerForVASTView:(STKVASTView *)view;

@end

@interface STKVASTView : UIView

@property (nonatomic, weak, nullable) id <STKVASTViewDelegate> delegate;

@property (nonatomic, weak, nullable) id <STKVASTViewDataSources> dataSources;

@property (nonatomic, copy, readonly, nullable) NSString *adCreative;

- (instancetype)initWithConfiguration:(STKVASTControllerConfiguration *)configuration;

- (void)loadForVastURL:(nullable NSURL *)vastURL;

- (void)loadForVastXML:(nullable NSData *)XML;

- (void)pause;

- (void)resume;

- (void)mute;

- (void)unmute;

@end

NS_ASSUME_NONNULL_END
