#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, STKMeasureObstructionType) {
    STKMeasureObstructionMediaControls,
    STKMeasureObstructionCloseAd,
    STKMeasureObstructionNotVisible,
    STKMeasureObstructionOther
};

@interface STKMeasureObstruction: NSObject

@property (nonatomic, strong) UIView *view;
@property (nonatomic, assign) STKMeasureObstructionType type;

+ (instancetype)obstructionWithView:(UIView *)view type:(STKMeasureObstructionType)type;
- (instancetype)initWithView:(UIView *)view obstructionType:(STKMeasureObstructionType)type;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
