      

Development Release Series 8.9
==============================

This is the development release series of HTCondor. The details of each
version are described below.

Version 8.9.1
-------------

Release Notes:

-  HTCondor version 8.9.1 not yet released.

New Features:

-  None.

Bugs Fixed:

-  None.

Version 8.9.0
-------------

Release Notes:

-  HTCondor version 8.9.0 not yet released.

New Features:

-  Normally, HTCondor requires the user to specify their credentials
   when using EC2 (via the grid universe or via *condor\_annex*). This
   allows users to use different accounts from the same machine.
   However, if a user started an EC2 instance with the privileges
   necessary to start other instances, and ran HTCondor in that
   instance, HTCondor was unable to use that instance’s privileges; the
   user still had to specify their credentials. Instead, the user may
   now specify “FROM INSTANCE” instead of the name of a credential file
   to indicate that HTCondor should use the instance’s credentials.

   By default, any user with access to a privileged EC2 instance has
   access to that instance’s privileges. If you would like to make use
   of this feature, please read `HTCondor Annex Customization
   Guide <../cloud-computing/annex-customization-guide.html>`__ before
   adding privileges (an instance role) to an instance which allows
   access by other users, specifically including the submitting of jobs
   to or running jobs on that instance. :ticket:`6789`

-  the *condor\_hdfs* daemon which allowed the hdfs daemons to run under
   the *condor\_master* has been removed from the contributed source.
   :ticket:`6809`
-  Scheduler Universe jobs now start in order of priority, instead of
   random order. This is most typically used for DAGMan. When running
   *condor\_submit\_dag* against a .dag file, you can use the -priority
   <N> flag to set the priority for the overall *condor\_dagman* job.
   When the *condor\_schedd* is starting new Scheduler Universe jobs,
   the highest priority queued job will start first. If all queued
   Scheduler Universe jobs have equal priority, they get started in
   order of subnmission. :ticket:`6703`

Bugs Fixed:

-  None.

      
