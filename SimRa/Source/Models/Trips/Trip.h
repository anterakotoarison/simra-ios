//
//  Trip.h
//  simra
//
//  Created by Christoph Krey on 28.03.19.
//  Copyright © 2019-2021 Mobile Cloud Computing an der Fakultät IV (Elektrotechnik und Informatik) der TU Berlin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreMotion/CoreMotion.h>
#import "UploaderObject.h"

NS_ASSUME_NONNULL_BEGIN

@interface TripAnnotation : NSObject
@property (strong, nonatomic) NSString *comment;
@property (nonatomic) BOOL frightening;
@property (nonatomic) BOOL car;
@property (nonatomic) BOOL taxi;
@property (nonatomic) BOOL delivery;
@property (nonatomic) BOOL bus;
@property (nonatomic) BOOL commercial;
@property (nonatomic) BOOL pedestrian;
@property (nonatomic) BOOL bicycle;
@property (nonatomic) BOOL motorcycle;
@property (nonatomic) BOOL other;
@property (nonatomic) BOOL escooter;
@property (nonatomic) NSInteger incidentId;

@end

@interface TripMotion : NSObject
@property (nonatomic) double x;
@property (nonatomic) double y;
@property (nonatomic) double z;
@property (nonatomic) double xl;
@property (nonatomic) double yl;
@property (nonatomic) double zl;
@property (nonatomic) double xr;
@property (nonatomic) double yr;
@property (nonatomic) double zr;
@property (nonatomic) double cr;
@property (nonatomic) NSTimeInterval timestamp;
@end

@interface TripGyro : NSObject
@property (nonatomic) double x;
@property (nonatomic) double y;
@property (nonatomic) double z;
@end

@interface ClosePassInfo: NSObject

@property (strong, nonatomic) CLLocation * location;
@property (strong, nonatomic) NSNumber * rightSensorValue; // total value
@property (strong, nonatomic) NSNumber * leftSensorValue; // total value
@property (strong, nonatomic) NSNumber * leftSensor1Value; // individual
@property (strong, nonatomic) NSNumber * leftSensor2Value; // individual
@property (strong, nonatomic) NSNumber * rightSensor1Value;// individual
@property (strong, nonatomic) NSNumber * rightSensor2Value;// individual

@property (nonatomic) int detectionType;
// detection type == 1 = user tapped the button
// detection type == 2 = automatic detection
@end

@interface TripLocation : NSObject
@property (strong, nonatomic) CLLocation *location;
@property (strong, nonatomic) TripGyro *gyro;
@property (strong, nonatomic) NSMutableArray <TripMotion *> *tripMotions;
@property (strong, nonatomic, nullable) TripAnnotation *tripAnnotation;
@property (strong, nonatomic) ClosePassInfo *closePassInfo;
@end

@interface TripInfo : NSObject
@property (nonatomic) NSInteger identifier;
@property (nonatomic) NSInteger version;
@property (nonatomic) Boolean edited;
@property (nonatomic) Boolean uploaded;
@property (nonatomic) NSURL *csvFile;
@property (nonatomic) Boolean statisticsAdded;
@property (nonatomic) NSInteger annotationsCount;
@property (nonatomic) NSInteger validAnnotationsCount;
@property (nonatomic) Boolean reUploaded;
@property (strong, nonatomic) NSString *fileHash;
@property (strong, nonatomic) NSString *filePasswd;
@property (nonatomic) NSDateInterval *duration;
@property (nonatomic) NSInteger length;

+ (NSArray <NSNumber *> *)allStoredIdentifiers;
- (instancetype)initFromStorage:(NSInteger)identifier;
@end

@interface Trip : UploaderObject <CLLocationManagerDelegate>
@property (nonatomic, readonly) NSInteger identifier;
@property (strong, nonatomic, readonly) CLLocation *startLocation;
@property (strong, nonatomic, readonly) CLLocation *lastLocation;
@property (strong, nonatomic, readonly) TripMotion *lastTripMotion;
@property (strong, nonatomic) NSMutableArray <TripLocation *> *tripLocations;

@property (nonatomic, readonly) NSInteger deferredSecs;
@property (nonatomic, readonly) NSInteger deferredMeters;
@property (nonatomic) NSInteger bikeTypeId;
@property (nonatomic) NSInteger positionId;
@property (nonatomic) NSInteger AIVersion;

@property (nonatomic) Boolean childseat;
@property (nonatomic) Boolean trailer;
@property (nonatomic) Boolean statisticsAdded;
@property (nonatomic) Boolean reUploaded;

+ (NSArray <NSNumber *> *)allStoredIdentifiers;
- (instancetype)initFromStorage:(NSInteger)identifier;
+ (void)deleteFromStorage:(NSInteger)identifier;
- (void)startRecording;
- (void)stopRecording;
- (NSInteger)tripAnnotations;
- (NSInteger)tripValidAnnotations;
- (NSInteger)numberOfScary;
- (NSDateInterval *)duration; //!depends on detailed locations
- (NSInteger)length; //!depends on detailed locations
- (NSInteger)idle;
- (TripInfo *)tripInfo;
- (void)successfullyReUploaded;
-(void)storeClosePassValueForTripWithLeftSensorVal:(NSNumber *)leftSensorVal
                                    rightSensorVal:(NSNumber *)rightSensorVal
                                    leftSensor1Val:(NSNumber *)leftSensor1Val
                                    leftSensor2Val:(NSNumber *)leftSensor2Val
                                   rightSensor1Val:(NSNumber *)rightSensor1Val
                                   rightSensor2Val:(NSNumber *)rightSensor2Val;
- (NSURL *)gpxFile;
- (NSURL *)geoJSONFile;
- (NSURL *)kmlFile;
@end

NS_ASSUME_NONNULL_END
