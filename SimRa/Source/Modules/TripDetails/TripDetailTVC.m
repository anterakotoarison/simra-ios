//
//  TripDetailTVC.m
//  SimRa
//
//  Created by Christoph Krey on 02.05.19.
//  Copyright © 2019-2021 Mobile Cloud Computing an der Fakultät IV (Elektrotechnik und Informatik) der TU Berlin. All rights reserved.
//

#import "TripDetailTVC.h"
#import "IdPicker.h"
#import "AppDelegate.h"

@interface TripDetailTVC ()
@property (weak, nonatomic) IBOutlet IdPicker *bikeType;
@property (weak, nonatomic) IBOutlet IdPicker *position;
@property (weak, nonatomic) IBOutlet UISwitch *childSeat;
@property (weak, nonatomic) IBOutlet UISwitch *trailer;

@property (nonatomic) BOOL changed;
@end

@implementation TripDetailTVC

- (void)viewDidLoad {
    [super viewDidLoad];
    
    AppDelegate *ad = [AppDelegate sharedDelegate];

    self.bikeType.array = [ad.constants valueForKey:@"bikeTypes"];
    self.position.array = [ad.constants valueForKey:@"positions"];

    [self update];
}

- (void)update {
    self.bikeType.arrayIndex = self.trip.bikeTypeId;
    self.position.arrayIndex = self.trip.positionId;
    self.childSeat.on = self.trip.childseat;
    self.trailer.on = self.trip.trailer;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.changed = FALSE;
    [self update];
}

- (void)viewWillDisappear:(BOOL)animated {
    if (self.changed) {
        [self performSegueWithIdentifier:@"attributesChanged:" sender:self];
    }
    [super viewWillDisappear:animated];
}

- (IBAction)bikeTypeChanged:(IdPicker *)sender {
    self.trip.bikeTypeId = sender.arrayIndex;
    self.changed = TRUE;
}

- (IBAction)positionChanged:(IdPicker *)sender {
    self.trip.positionId = sender.arrayIndex;
    self.changed = TRUE;
}

- (IBAction)childSeatChanged:(UISwitch *)sender {
    self.trip.childseat = sender.on;
    self.changed = TRUE;
}

- (IBAction)trailerChanged:(UISwitch *)sender {
    self.trip.trailer = sender.on;
    self.changed = TRUE;
}

- (IBAction)setDefaultPressed:(UIBarButtonItem *)sender {
//    AppDelegate *ad = [AppDelegate sharedDelegate];
//    [ad.defaults setInteger:self.trip.bikeTypeId forKey:@"bikeTypeId"];
    [Utility saveIntWithKey:@"bikeTypeId" value:self.trip.bikeTypeId];

//    [ad.defaults setInteger:self.trip.positionId forKey:@"positionId"];
    [Utility saveIntWithKey:@"positionId" value:self.trip.positionId];

//    [ad.defaults setBool:self.trip.childseat forKey:@"childSeat"];
    //    [ad.defaults setBool:self.trip.trailer forKey:@"trailer"];

    [Utility saveBoolWithKey:@"childSeat" value:self.trip.childseat];
    [Utility saveBoolWithKey:@"trailer" value:self.trip.trailer];

}

@end
