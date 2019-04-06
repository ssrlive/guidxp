//
//  ViewController.m
//

#import "ViewController.h"
#import "guidxp.h"

@interface ViewController ()

@end

@implementation ViewController {
    __weak IBOutlet UILabel *_resultLabel;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (IBAction)generateTapped:(UIButton *)sender {
    char uuid[40];
    generate_guid(uuid, sizeof(uuid));
    _resultLabel.text = [NSString stringWithUTF8String:uuid];
}

@end
