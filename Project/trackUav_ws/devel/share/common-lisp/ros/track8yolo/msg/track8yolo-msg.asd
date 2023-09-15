
(cl:in-package :asdf)

(defsystem "track8yolo-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "BoundingBox" :depends-on ("_package_BoundingBox"))
    (:file "_package_BoundingBox" :depends-on ("_package"))
  ))