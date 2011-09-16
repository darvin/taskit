//  Taskit
//  Written by Alex Gordon on 09/09/2011.
//  Licensed under the WTFPL: http://sam.zoy.org/wtfpl/

#import <Foundation/Foundation.h>

@interface Taskit : NSObject
{
    BOOL hasLaunched;
    
    NSString *launchPath;
    NSMutableArray *arguments;
    NSMutableDictionary *environment;
    NSString *workingDirectory;
    
    NSData *input;
    NSString *inputString;
    
    //TODO: BOOL usesAuthorization;
    
    NSPipe *inPipe;
    NSPipe *outPipe;
    NSPipe *errPipe;
        
    pid_t pid;
    int waitpid_status;
    BOOL isRunning;
    
    void (^receivedOutputData)(NSData *output);
    void (^receivedOutputString)(NSString *outputString);
    
    void (^receivedErrorData)(NSData *err);
    void (^receivedErrorString)(NSString *errString);
}

+ (id)task;
- (id)init;

#pragma mark Setup

@property (copy) NSString *launchPath;
@property (readonly) NSMutableArray *arguments;
@property (readonly) NSMutableDictionary *environment;
@property (copy) NSString *workingDirectory;

@property (copy) NSData *input;
@property (copy) NSString *inputString;

- (void)populateWithCurrentEnvironment;

//TODO: @property (assign) BOOL usesAuthorization;

#pragma mark Concurrency
@property (copy) void (^receivedOutputData)(NSData *output);
@property (copy) void (^receivedOutputString)(NSString *outputString);
@property (copy) void (^receivedErrorData)(NSData *err);
@property (copy) void (^receivedErrorString)(NSString *errString);
//TODO: @property (copy) void (^processExited)(NSString *outputString);

#pragma mark Control
- (BOOL)launch;

//TODO: - (void)interrupt; // Not always possible. Sends SIGINT.
//TODO: - (void)terminate; // Not always possible. Sends SIGTERM.

//TODO: - (BOOL)suspend;
//TODO: - (BOOL)resume;

#pragma mark Blocking methods
- (void)waitUntilExit;

- (NSData *)waitForOutput;
- (NSString *)waitForOutputString;

- (NSData *)waitForError;
- (NSString *)waitForErrorString;

@end