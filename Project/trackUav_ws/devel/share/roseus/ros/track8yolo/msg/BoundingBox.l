;; Auto-generated. Do not edit!


(when (boundp 'track8yolo::BoundingBox)
  (if (not (find-package "TRACK8YOLO"))
    (make-package "TRACK8YOLO"))
  (shadow 'BoundingBox (find-package "TRACK8YOLO")))
(unless (find-package "TRACK8YOLO::BOUNDINGBOX")
  (make-package "TRACK8YOLO::BOUNDINGBOX"))

(in-package "ROS")
;;//! \htmlinclude BoundingBox.msg.html


(defclass track8yolo::BoundingBox
  :super ros::object
  :slots (_xmin _ymin _xmax _ymax _label ))

(defmethod track8yolo::BoundingBox
  (:init
   (&key
    ((:xmin __xmin) 0)
    ((:ymin __ymin) 0)
    ((:xmax __xmax) 0)
    ((:ymax __ymax) 0)
    ((:label __label) 0)
    )
   (send-super :init)
   (setq _xmin (round __xmin))
   (setq _ymin (round __ymin))
   (setq _xmax (round __xmax))
   (setq _ymax (round __ymax))
   (setq _label (round __label))
   self)
  (:xmin
   (&optional __xmin)
   (if __xmin (setq _xmin __xmin)) _xmin)
  (:ymin
   (&optional __ymin)
   (if __ymin (setq _ymin __ymin)) _ymin)
  (:xmax
   (&optional __xmax)
   (if __xmax (setq _xmax __xmax)) _xmax)
  (:ymax
   (&optional __ymax)
   (if __ymax (setq _ymax __ymax)) _ymax)
  (:label
   (&optional __label)
   (if __label (setq _label __label)) _label)
  (:serialization-length
   ()
   (+
    ;; int64 _xmin
    8
    ;; int64 _ymin
    8
    ;; int64 _xmax
    8
    ;; int64 _ymax
    8
    ;; int64 _label
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _xmin
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _xmin (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _xmin) (= (length (_xmin . bv)) 2)) ;; bignum
              (write-long (ash (elt (_xmin . bv) 0) 0) s)
              (write-long (ash (elt (_xmin . bv) 1) -1) s))
             ((and (class _xmin) (= (length (_xmin . bv)) 1)) ;; big1
              (write-long (elt (_xmin . bv) 0) s)
              (write-long (if (>= _xmin 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _xmin s)(write-long (if (>= _xmin 0) 0 #xffffffff) s)))
     ;; int64 _ymin
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _ymin (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _ymin) (= (length (_ymin . bv)) 2)) ;; bignum
              (write-long (ash (elt (_ymin . bv) 0) 0) s)
              (write-long (ash (elt (_ymin . bv) 1) -1) s))
             ((and (class _ymin) (= (length (_ymin . bv)) 1)) ;; big1
              (write-long (elt (_ymin . bv) 0) s)
              (write-long (if (>= _ymin 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _ymin s)(write-long (if (>= _ymin 0) 0 #xffffffff) s)))
     ;; int64 _xmax
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _xmax (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _xmax) (= (length (_xmax . bv)) 2)) ;; bignum
              (write-long (ash (elt (_xmax . bv) 0) 0) s)
              (write-long (ash (elt (_xmax . bv) 1) -1) s))
             ((and (class _xmax) (= (length (_xmax . bv)) 1)) ;; big1
              (write-long (elt (_xmax . bv) 0) s)
              (write-long (if (>= _xmax 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _xmax s)(write-long (if (>= _xmax 0) 0 #xffffffff) s)))
     ;; int64 _ymax
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _ymax (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _ymax) (= (length (_ymax . bv)) 2)) ;; bignum
              (write-long (ash (elt (_ymax . bv) 0) 0) s)
              (write-long (ash (elt (_ymax . bv) 1) -1) s))
             ((and (class _ymax) (= (length (_ymax . bv)) 1)) ;; big1
              (write-long (elt (_ymax . bv) 0) s)
              (write-long (if (>= _ymax 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _ymax s)(write-long (if (>= _ymax 0) 0 #xffffffff) s)))
     ;; int64 _label
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _label (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _label) (= (length (_label . bv)) 2)) ;; bignum
              (write-long (ash (elt (_label . bv) 0) 0) s)
              (write-long (ash (elt (_label . bv) 1) -1) s))
             ((and (class _label) (= (length (_label . bv)) 1)) ;; big1
              (write-long (elt (_label . bv) 0) s)
              (write-long (if (>= _label 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _label s)(write-long (if (>= _label 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _xmin
#+(or :alpha :irix6 :x86_64)
      (setf _xmin (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _xmin (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _ymin
#+(or :alpha :irix6 :x86_64)
      (setf _ymin (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _ymin (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _xmax
#+(or :alpha :irix6 :x86_64)
      (setf _xmax (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _xmax (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _ymax
#+(or :alpha :irix6 :x86_64)
      (setf _ymax (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _ymax (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _label
#+(or :alpha :irix6 :x86_64)
      (setf _label (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _label (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(setf (get track8yolo::BoundingBox :md5sum-) "e3356b77b350c7150522a34c60a8a840")
(setf (get track8yolo::BoundingBox :datatype-) "track8yolo/BoundingBox")
(setf (get track8yolo::BoundingBox :definition-)
      "int64 xmin
int64 ymin
int64 xmax
int64 ymax
int64 label
")



(provide :track8yolo/BoundingBox "e3356b77b350c7150522a34c60a8a840")


