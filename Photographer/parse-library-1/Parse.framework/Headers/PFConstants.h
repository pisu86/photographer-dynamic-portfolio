// PFConstants.h
// Copyright 2011 Parse, Inc. All rights reserved.

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <Parse/PFNullability.h>
#else
#import <ParseOSX/PFNullability.h>
#endif

@class PFObject;
@class PFUser;

///--------------------------------------
/// @name Version
///--------------------------------------

#define PARSE_VERSION @"1.6.4"

extern NSInteger const PARSE_API_VERSION;

///--------------------------------------
/// @name Platform
///--------------------------------------

#define PARSE_IOS_ONLY (TARGET_OS_IPHONE)
#define PARSE_OSX_ONLY (TARGET_OS_MAC && !(TARGET_OS_IPHONE))

extern NSString *const PF_NONNULL_S kPFDeviceType;

#if PARSE_IOS_ONLY
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
@compatibility_alias UIImage NSImage;
@compatibility_alias UIColor NSColor;
@compatibility_alias UIView NSView;
#endif

///--------------------------------------
/// @name Server
///--------------------------------------

extern NSString *const PF_NONNULL_S kPFParseServer;

///--------------------------------------
/// @name Cache Policies
///--------------------------------------

/*!
 `PFCachePolicy` specifies different caching policies that could be used with <PFQuery>.

 This lets you show data when the user's device is offline,
 or when the app has just started and network requests have not yet had time to complete.
 Parse takes care of automatically flushing the cache when it takes up too much space.

 @warning Cache policy could only be set when Local Datastore is not enabled.

 @see PFQuery
 */
typedef NS_ENUM(uint8_t, PFCachePolicy) {
    /*!
     @abstract The query does not load from the cache or save results to the cache.
     This is the default cache policy.
     */
    kPFCachePolicyIgnoreCache = 0,
    /*!
     @abstract The query only loads from the cache, ignoring the network.
     If there are no cached results, this causes a `NSError` with `kPFErrorCacheMiss` code.
     */
    kPFCachePolicyCacheOnly,
    /*!
     @abstract The query does not load from the cache, but it will save results to the cache.
     */
    kPFCachePolicyNetworkOnly,
    /*!
     @abstract The query first tries to load from the cache, but if that fails, it loads results from the network.
     If there are no cached results, this causes a `NSError` with `kPFErrorCacheMiss` code.
     */
    kPFCachePolicyCacheElseNetwork,
    /*!
     @abstract The query first tries to load from the network, but if that fails, it loads results from the cache.
     If there are no cached results, this causes a `NSError` with `kPFErrorCacheMiss` code.
     */
    kPFCachePolicyNetworkElseCache,
    /*!
     @abstract The query first loads from the cache, then loads from the network.
     The callback will be called twice - first with the cached results, then with the network results.
     Since it returns two results at different times, this cache policy cannot be used with synchronous or task methods.
     */
    kPFCachePolicyCacheThenNetwork
};

///--------------------------------------
/// @name Logging Levels
///--------------------------------------

/*!
 `PFLogLevel` enum specifies different levels of logging that could be used to limit or display more messages in logs.

 @see [Parse setLogLevel:]
 @see [Parse logLevel]
 */
typedef NS_ENUM(uint8_t, PFLogLevel) {
    /*!
     Log level that disables all logging.
     */
    PFLogLevelNone = 0,
    /*!
     Log level that if set is going to output error messages to the log.
     */
    PFLogLevelError = 1,
    /*!
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     */
    PFLogLevelWarning = 2,
    /*!
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     - Informational messages
     */
    PFLogLevelInfo = 3,
    /*!
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     - Informational messages
     - Debug messages
     */
    PFLogLevelDebug = 4
};

///--------------------------------------
/// @name Errors
///--------------------------------------

extern NSString *const PF_NONNULL_S PFParseErrorDomain;

/*! @abstract 1: Internal server error. No information available. */
extern NSInteger const kPFErrorInternalServer;

/*! @abstract 100: The connection to the Parse servers failed. */
extern NSInteger const kPFErrorConnectionFailed;
/*! @abstract 101: Object doesn't exist, or has an incorrect password. */
extern NSInteger const kPFErrorObjectNotFound;
/*! @abstract 102: You tried to find values matching a datatype that doesn't support exact database matching, like an array or a dictionary. */
extern NSInteger const kPFErrorInvalidQuery;
/*! @abstract 103: Missing or invalid classname. Classnames are case-sensitive. They must start with a letter, and a-zA-Z0-9_ are the only valid characters. */
extern NSInteger const kPFErrorInvalidClassName;
/*! @abstract 104: Missing object id. */
extern NSInteger const kPFErrorMissingObjectId;
/*! @abstract 105: Invalid key name. Keys are case-sensitive. They must start with a letter, and a-zA-Z0-9_ are the only valid characters. */
extern NSInteger const kPFErrorInvalidKeyName;
/*! @abstract 106: Malformed pointer. Pointers must be arrays of a classname and an object id. */
extern NSInteger const kPFErrorInvalidPointer;
/*! @abstract 107: Malformed json object. A json dictionary is expected. */
extern NSInteger const kPFErrorInvalidJSON;
/*! @abstract 108: Tried to access a feature only available internally. */
extern NSInteger const kPFErrorCommandUnavailable;
/*! @abstract 111: Field set to incorrect type. */
extern NSInteger const kPFErrorIncorrectType;
/*! @abstract 112: Invalid channel name. A channel name is either an empty string (the broadcast channel) or contains only a-zA-Z0-9_ characters and starts with a letter. */
extern NSInteger const kPFErrorInvalidChannelName;
/*! @abstract 114: Invalid device token. */
extern NSInteger const kPFErrorInvalidDeviceToken;
/*! @abstract 115: Push is misconfigured. See details to find out how. */
extern NSInteger const kPFErrorPushMisconfigured;
/*! @abstract 116: The object is too large. */
extern NSInteger const kPFErrorObjectTooLarge;
/*! @abstract 119: That operation isn't allowed for clients. */
extern NSInteger const kPFErrorOperationForbidden;
/*! @abstract 120: The results were not found in the cache. */
extern NSInteger const kPFErrorCacheMiss;
/*! @abstract 121: Keys in NSDictionary values may not include '$' or '.'. */
extern NSInteger const kPFErrorInvalidNestedKey;
/*! @abstract 122: Invalid file name. A file name contains only a-zA-Z0-9_. characters and is between 1 and 36 characters. */
extern NSInteger const kPFErrorInvalidFileName;
/*! @abstract 123: Invalid ACL. An ACL with an invalid format was saved. This should not happen if you use PFACL. */
extern NSInteger const kPFErrorInvalidACL;
/*! @abstract 124: The request timed out on the server. Typically this indicates the request is too expensive. */
extern NSInteger const kPFErrorTimeout;
/*! @abstract 125: The email address was invalid. */
extern NSInteger const kPFErrorInvalidEmailAddress;
/*! @abstract 137: A unique field was given a value that is already taken. */
extern NSInteger const kPFErrorDuplicateValue;
/*! @abstract 139: Role's name is invalid. */
extern NSInteger const kPFErrorInvalidRoleName;
/*! @abstract 140: Exceeded an application quota.  Upgrade to resolve. */
extern NSInteger const kPFErrorExceededQuota;
/*! @abstract 141: Cloud Code script had an error. */
extern NSInteger const kPFScriptError;
/*! @abstract 142: Cloud Code validation failed. */
extern NSInteger const kPFValidationError;
/*! @abstract 143: Product purchase receipt is missing */
extern NSInteger const kPFErrorReceiptMissing;
/*! @abstract 144: Product purchase receipt is invalid */
extern NSInteger const kPFErrorInvalidPurchaseReceipt;
/*! @abstract 145: Payment is disabled on this device */
extern NSInteger const kPFErrorPaymentDisabled;
/*! @abstract 146: The product identifier is invalid */
extern NSInteger const kPFErrorInvalidProductIdentifier;
/*! @abstract 147: The product is not found in the App Store */
extern NSInteger const kPFErrorProductNotFoundInAppStore;
/*! @abstract 148: The Apple server response is not valid */
extern NSInteger const kPFErrorInvalidServerResponse;
/*! @abstract 149: Product fails to download due to file system error */
extern NSInteger const kPFErrorProductDownloadFileSystemFailure;
/*! @abstract 150: Fail to convert data to image. */
extern NSInteger const kPFErrorInvalidImageData;
/*! @abstract 151: Unsaved file. */
extern NSInteger const kPFErrorUnsavedFile;
/*! @abstract 153: Fail to delete file. */
extern NSInteger const kPFErrorFileDeleteFailure;
/*! @abstract 155: Application has exceeded its request limit. */
extern NSInteger const kPFErrorRequestLimitExceeded;
/*! @abstract 160: Invalid event name. */
extern NSInteger const kPFErrorInvalidEventName;
/*! @abstract 200: Username is missing or empty */
extern NSInteger const kPFErrorUsernameMissing;
/*! @abstract 201: Password is missing or empty */
extern NSInteger const kPFErrorUserPasswordMissing;
/*! @abstract 202: Username has already been taken */
extern NSInteger const kPFErrorUsernameTaken;
/*! @abstract 203: Email has already been taken */
extern NSInteger const kPFErrorUserEmailTaken;
/*! @abstract 204: The email is missing, and must be specified */
extern NSInteger const kPFErrorUserEmailMissing;
/*! @abstract 205: A user with the specified email was not found */
extern NSInteger const kPFErrorUserWithEmailNotFound;
/*! @abstract 206: The user cannot be altered by a client without the session. */
extern NSInteger const kPFErrorUserCannotBeAlteredWithoutSession;
/*! @abstract 207: Users can only be created through sign up */
extern NSInteger const kPFErrorUserCanOnlyBeCreatedThroughSignUp;
/*! @abstract 208: An existing Facebook account already linked to another user. */
extern NSInteger const kPFErrorFacebookAccountAlreadyLinked;
/*! @abstract 208: An existing account already linked to another user. */
extern NSInteger const kPFErrorAccountAlreadyLinked;
/*! @abstract 209: User ID mismatch */
extern NSInteger const kPFErrorUserIdMismatch;
/*! @abstract 250: Facebook id missing from request */
extern NSInteger const kPFErrorFacebookIdMissing;
/*! @abstract 250: Linked id missing from request */
extern NSInteger const kPFErrorLinkedIdMissing;
/*! @abstract 251: Invalid Facebook session */
extern NSInteger const kPFErrorFacebookInvalidSession;
/*! @abstract 251: Invalid linked session */
extern NSInteger const kPFErrorInvalidLinkedSession;

///--------------------------------------
/// @name Blocks
///--------------------------------------

typedef void (^PFBooleanResultBlock)(BOOL succeeded, NSError * __nullable error);
typedef void (^PFIntegerResultBlock)(int number, NSError * __nullable error);
typedef void (^PFArrayResultBlock)(NSArray * __nullable objects, NSError * __nullable error);
typedef void (^PFObjectResultBlock)(PFObject * __nullable object, NSError * __nullable error);
typedef void (^PFSetResultBlock)(NSSet * __nullable channels, NSError * __nullable error);
typedef void (^PFUserResultBlock)(PFUser * __nullable user, NSError * __nullable error);
typedef void (^PFDataResultBlock)(NSData * __nullable data, NSError * __nullable error);
typedef void (^PFDataStreamResultBlock)(NSInputStream * __nullable stream, NSError * __nullable error);
typedef void (^PFStringResultBlock)(NSString * __nullable string, NSError * __nullable error);
typedef void (^PFIdResultBlock)(PF_NULLABLE_S id object, NSError * __nullable error);
typedef void (^PFProgressBlock)(int percentDone);

///--------------------------------------
/// @name Deprecated Macros
///--------------------------------------

#ifndef PARSE_DEPRECATED
#  ifdef __deprecated_msg
#    define PARSE_DEPRECATED(_MSG) __deprecated_msg(_MSG)
#  else
#    ifdef __deprecated
#      define PARSE_DEPRECATED(_MSG) __attribute__((deprecated))
#    else
#      define PARSE_DEPRECATED(_MSG)
#    endif
#  endif
#endif
