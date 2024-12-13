//
//  STKVASTController.h
//
//  Copyright © 2016 Appodeal, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <StackModules/StackModules.h>
#import <StackRendering/STKVASTControllerConfiguration.h>


@class STKVASTController;

NS_ASSUME_NONNULL_BEGIN

@protocol STKVASTControllerDelegate <NSObject>

@required

/// Called after successful loading video url
/// @param controller Current VAST Controller
- (void)vastControllerReady:(STKVASTController *)controller;
/// Called after not successful loading video url
/// @param controller Current VAST Controller
/// @param error Loading video error
- (void)vastController:(STKVASTController *)controller didFailToLoad:(NSError *)error;
/// Called after not successful loading video url in preload mode
/// @param controller Current VAST Controller
- (void)vastController:(STKVASTController *)controller didExpireWithError:(NSError *)error;
 /// Called after not successful presenting video url
 /// @param controller Current VAST Controller
 /// @param error Presentation error
- (void)vastController:(STKVASTController *)controller didFailWhileShow:(NSError *)error;
/// Called after successful presenting video url
/// @param controller Current VAST Controller
- (void)vastControllerDidPresent:(STKVASTController *)controller;
/// Called after fully watched video
/// @param controller Current VAST Controller
- (void)vastControllerDidFinish:(STKVASTController *)controller;
/// Called when vast controller opens product in safari
/// @param controller Presented controller
- (void)vastControllerWillLeaveApplication:(STKVASTController *)controller;
/// Called when vast controller opens SKStoreProductViewController
/// @param controller Presented controller
- (void)vastControllerWillPresentProductScreen:(STKVASTController *)controller;
/// Called when vast controller dismiss SKStoreProductViewController
/// @param controller Presented controller
- (void)vastControllerDidDismissProductScreen:(STKVASTController *)controller;
/// Called after controller did dismiss
/// @param controller Current VAST Controller
- (void)vastControllerDidDismiss:(STKVASTController *)controller;
/// Called after controller did impression
/// @param controller Current VAST Controller
- (void)vastControllerDidImpression:(STKVASTController *)controller;

@optional

/// Called before controller will start clich through processing
/// @param controller Presented controller
/// @param URL Destination URL
- (BOOL)vastController:(STKVASTController *)controller shouldProcessNavigationWithURL:(NSURL *)URL;
/// Called if video was skipped
/// @param controller Current VAST Controller
- (void)vastControllerDidSkip:(STKVASTController *)controller;

@end

@interface STKVASTController : STKRotationController
/// Presentation VASTController delegate
@property (nonatomic, weak, nullable) id <STKVASTControllerDelegate> delegate;
/// VAST XML Creative
@property (nonatomic, copy, readonly, nullable) NSString *adCreative;
/// Initializer
/// @param configuration VAST controller configuration
- (instancetype)initWithConfiguration:(STKVASTControllerConfiguration *)configuration;
/// Prepare controller for test mode
/// @param testing Set YES if test mode enabled
+ (void)prepareForTesting:(BOOL)testing;
/// Start load vast with url
/// @param vastURL vast url source
- (void)loadForVastURL:(nullable NSURL *)vastURL;
/// Start load vast with xml document
/// @param XML vast document
- (void)loadForVastXML:(nullable NSData *)XML;
/// Show vast controller on this controller
/// @param viewController Presenting view controller
- (void)presentFromViewController:(nullable UIViewController *)viewController;
/// Suspend vast player
- (void)pause;
/// Resume vast player
- (void)resume;
@end

NS_ASSUME_NONNULL_END
